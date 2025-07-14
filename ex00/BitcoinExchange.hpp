#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <string>
# include <map>
# include <iostream>
# include <fstream>
# include <sstream>
# include <algorithm>

class BitcoinExchange
{
private:
    std::map<std::string, float> _data;

    void loadDatabase(const std::string& filename);
    bool isValidDate(const std::string& date) const;
    bool isValidValue(float value) const;
    float getExchangeRate(const std::string& date) const;

public:
    BitcoinExchange();
    BitcoinExchange(const std::string& databaseFilename);
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();

    void processInputFile(const std::string& inputFilename);
};

#endif 