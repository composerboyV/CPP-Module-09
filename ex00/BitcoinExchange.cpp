#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const std::string& databaseFilename)
{
    loadDatabase(databaseFilename);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
    *this = other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)
    {
        _data = other._data;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::loadDatabase(const std::string& filename)
{
    std::ifstream ifs(filename.c_str());
    if (!ifs.is_open())
    {
        std::cerr << "Error: could not open database file." << std::endl;
        exit(1);
    }

    std::string line;
    std::getline(ifs, line); // Skip header line

    while (std::getline(ifs, line))
    {
        std::stringstream ss(line);
        std::string date_str;
        std::string value_str;

        if (std::getline(ss, date_str, ',') && std::getline(ss, value_str))
        {
            float rate_val;
            std::stringstream ss_rate(value_str);
            if (!(ss_rate >> rate_val) || ss_rate.fail() || !ss_rate.eof()) {
                std::cerr << "Error: bad data in database (invalid float) => " << line << std::endl;
            } else {
                _data[date_str] = rate_val;
            }
        }
    }
    ifs.close();
}

bool BitcoinExchange::isValidDate(const std::string& date) const
{
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;

    for (int i = 0; i < 10; ++i)
    {
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(date[i]))
            return false;
    }

    int year, month, day;
    std::stringstream ss_year(date.substr(0, 4));
    if (!(ss_year >> year) || ss_year.fail() || !ss_year.eof()) return false;

    std::stringstream ss_month(date.substr(5, 2));
    if (!(ss_month >> month) || ss_month.fail() || !ss_month.eof()) return false;

    std::stringstream ss_day(date.substr(8, 2));
    if (!(ss_day >> day) || ss_day.fail() || !ss_day.eof()) return false;

    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;

    if (month == 2)
    {
        bool is_leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        if (day > (29 - !is_leap))
            return false;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day > 30)
            return false;
    }
    return true;
}

bool BitcoinExchange::isValidValue(float value) const
{
    return (value >= 0 && value <= 1000);
}

float BitcoinExchange::getExchangeRate(const std::string& date) const
{
    std::map<std::string, float>::const_iterator it = _data.find(date);
    if (it != _data.end())
    {
        return it->second;
    }

    // If exact date not found, find the closest lower date
    it = _data.upper_bound(date);
    if (it == _data.begin())
    {
        std::cerr << "Error: no data found for date or earlier date." << std::endl;
        return -1.0f; // Indicate error
    }
    --it;
    return it->second;
}

void BitcoinExchange::processInputFile(const std::string& inputFilename)
{
    std::ifstream ifs(inputFilename.c_str());
    if (!ifs.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    std::getline(ifs, line); // Skip header line

    while (std::getline(ifs, line))
    {
        // Skip empty lines
        if (line.empty() || line.find_first_not_of(" \t\r\n") == std::string::npos)
            continue;

        std::string date_str;
        std::string value_str;
        float value = -1.0f;

        size_t delimiter_pos = line.find(" | ");
        if (delimiter_pos == std::string::npos)
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        date_str = line.substr(0, delimiter_pos);
        value_str = line.substr(delimiter_pos + 3);

        // Trim whitespace from date_str and value_str
        date_str.erase(0, date_str.find_first_not_of(" \t\n\r"));
        date_str.erase(date_str.find_last_not_of(" \t\n\r") + 1);
        value_str.erase(0, value_str.find_first_not_of(" \t\n\r"));
        value_str.erase(value_str.find_last_not_of(" \t\n\r") + 1);

        if (!isValidDate(date_str))
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        std::stringstream ss_value(value_str);
        ss_value >> value; // Attempt to read the float value

        // Check if the conversion failed or if there are leftover characters after the number
        if (ss_value.fail() || !ss_value.eof()) {
             std::cerr << "Error: not a number => " << line << std::endl;
             continue;
        }
        
        if (!isValidValue(value))
        {
            if (value < 0)
                std::cerr << "Error: not a positive number." << std::endl;
            else // value > 1000
                std::cerr << "Error: too large a number." << std::endl;
            continue;
        }

        float rate = getExchangeRate(date_str);
        if (rate == -1.0f) // Error from getExchangeRate
        {
            continue;
        }
        
        std::cout << date_str << " => " << value << " = " << value * rate << std::endl;
    }
    ifs.close();
}
