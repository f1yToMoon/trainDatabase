#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>

int main()
{
    int rowsNum = 15
            ;
    std::fstream fout;
    srand (time(nullptr));
    fout.open("reference.csv", std::ios::out | std::ios::trunc);
    std::string tmp;

    std::ifstream maleNF("male_name.txt");
    std::vector<std::string> maleN;
    while (getline(maleNF, tmp)) {
        maleN.push_back(tmp);
    }
    std::ifstream name2F("name2.txt");
    std::vector<std::string> name2;
    while (getline(name2F, tmp)) {
        name2.push_back(tmp);
    }
    std::ifstream name3F("name3.txt");
    std::vector<std::string> name3;
    while (getline(name3F, tmp)) {
        name3.push_back(tmp);
    }
    std::ifstream femaleNF("female_name.txt");
    std::vector<std::string> femaleN;
    while (getline(femaleNF, tmp)) {
        femaleN.push_back(tmp);
    }
    std::ifstream citiesF("cities.txt");
    std::vector<std::string> cities;
    while (getline(citiesF, tmp)) {
        cities.push_back(tmp);
    }
    maleNF.close();
    name2F.close();
    name3F.close();
    femaleNF.close();
    citiesF.close();

    std::vector<std::pair<std::string, float>> fastClasses = {{"1P", 1.45}, {"1B", 2.5}, {"1C", 1.11}, {"2B", 2.7}, {"2C", 1.31}, {"2E", 1.65}};
    std::vector<std::pair<std::string, float>> fastClasses2 = {{"1E", 2.22}, {"1P", 4.6}, {"2C", 1.9}};
    std::vector<std::pair<std::string, float>> casualClasses = {{"1C", 1.1}, {"1P", 1.2}, {"1B", 1.3}, {"1Б", 1.4}, {"1Л", 1.5}, {"1И", 1.6}, {"1A", 1.7}, {"2C", 1.8}, {"2P", 1.99}, {"2E", 1.8}, {"2Э", 1.88}, {"3Э", 1.888}};
    std::vector<std::string> banksNum = {"225", "653", "602", "641", "608", "607", "603", "674", "187", "411", "832", "545", "818", "788", "728", "802", "063", "593", "824", "774", "207", "786", "752", "770"};
    /// 225 - 674 сбер
    /// 187 - 063 втб
    /// 593 - 770 альфа
    std::string passportNum, dateFrom, dateTo, voyage, placePrice, card, fromPlace, toPlace;
    std::string firstName, secondName, thirdName;
    int cn = 0;
    for (int i = 0; i < rowsNum; ++i) {

        ///create people
        int gender = rand() % 2;
        if (gender == 0) {
            firstName = maleN[rand() % maleN.size()] + " ";
            secondName = name2[rand() % name2.size()] + " ";
            thirdName = name3[rand() % name3.size()] + "ич ";
        } else {
            firstName = femaleN[rand() % femaleN.size()] + " ";
            secondName = name2[rand() % name2.size()] + "a ";
            thirdName = name3[rand() % name3.size()] + "на ";
        }

        ///cities
        int from = rand() % cities.size();
        int to = rand() % cities.size();
        while (from == to) {
            to = rand() % cities.size();
        }
        fromPlace = cities[from];
        toPlace = cities[to];

        ///passport and date
        int day = rand() % 27 + 1;
        int month = rand() % 12 + 1;
        int diff = 28 - day;
        std::stringstream s, s1, s2, s3, s4, s5;
        s << std::setw(2) << std::setfill('0') << rand() % 99 + 1 << " " << std::setw(2) << std::setfill('0') << rand() % 22 << " " << std::setw(6) << std::setfill('0') << rand() % 1000000;
        passportNum = s.str();
        s1 << "2022-" << std::setw(2) << std::setfill('0') << month << "-" << std::setw(2) << std::setfill('0') << day << "T" << std::setw(2) << std::setfill('0') << rand() % 24 << ":" << std::setw(2) << std::setfill('0') << rand() % 60;
        dateFrom = s1.str();
        s2 << "2022-" << std::setw(2) << std::setfill('0') << month << "-" << std::setw(2) << std::setfill('0') << day + (rand() % diff + 1) << "T" << std::setw(2) << std::setfill('0') << rand() % 24 << ":" << std::setw(2) << std::setfill('0') << rand() % 60;
        dateTo = s2.str();

        ///voyage
        int voyageNum = rand() % 788 + 1;
        if (voyageNum >= 151 && voyageNum <= 298 && (month == 6 || month == 7 || month == 8)) {
            s3 << voyageNum << "s";
        } else if (voyageNum >= 451 && voyageNum <= 598 && (month == 9 || month == 10)) {
            s3 << voyageNum << "s";
        } else if (voyageNum >= 701 && voyageNum <= 750) {
            s3 << voyageNum << "A";
        } else if (voyageNum >= 751 && voyageNum <= 788) {
            s3 << voyageNum << "C";
        } else {
            voyageNum = rand() % 150 + 1;
            s3 << voyageNum;
        }
        voyage = s3.str();

        ///carriage, place and price
        int cost = 150;
        int carriage = rand() % 12 + 9;
        int place = rand() % 21 + 1;
        if (voyageNum >= 751 && voyageNum <= 788) {
            int rFast = rand() % fastClasses.size();
            if (rFast == 5) {
                s4 << carriage << "(" << fastClasses[rFast].first << ")-" << place << "," << cost * fastClasses[rFast].second * diff + 2000;
            } else if (carriage == 10 || carriage == 20) {
                s4 << carriage << "(2B)-" << rand() % 21 << "," << cost * 1 * diff;
            } else {
                s4 << carriage << "(" << fastClasses[rFast].first << ")-" << place << "," << cost * fastClasses[rFast].second * diff;
            }
        } else if (voyageNum >= 701 && voyageNum <= 750) {
            int rFast2 = rand() % fastClasses2.size();
            s4 << carriage << "(" << fastClasses2[rFast2].first << ")-" << place << "," << cost * fastClasses2[rFast2].second * diff;
        } else {
            int rCasual = rand() % casualClasses.size();
            s4 << carriage << "(" << casualClasses[rCasual].first << ")-" << place << "," << cost * casualClasses[rCasual].second * diff;
        }
        placePrice = s4.str();
        if (cn == 0) {
            ///cards with settings
            double val = (double) rand() / RAND_MAX;

            int ran_pay;
            if (val < 0.1) {           ///10%
                ran_pay = 2;
            } else if (val < 0.30) {   ///20%
                ran_pay = 3;
            } else if (val < 0.60) {   ///30%
                ran_pay = 4;
            } else if (val < 0.95) {   ///35%
                ran_pay = 5;
            } else {                   ///5%
                ran_pay = 6;
            }

            int ind;
            if (val < 0.4) {           ///40%
                ind = 0;
            } else if (val < 0.9) {    ///50%
                ind = 1;
            } else {                   ///10%
                ind = 2;
            }

            int bankNum;
            switch (ind) {
                case 0:
                    bankNum = rand() % 8;      ///сбер
                    break;
                case 1:
                    bankNum = rand() % 9 + 8;  ///втб
                    break;
                case 2:
                    bankNum = rand() % 7 + 17; ///альфа
            }
            ///ran_pay: 2 - МИP; 3 - American Express; 4 - VISA; 5 - MasterCard; 6 - Maestro
            s5 << ran_pay << "04" << std::setw(2) << std::setfill('0') << rand() % 99 + 1 << std::setw(2)
               << std::setfill('0') << rand() % 100 << banksNum[bankNum] << std::setw(6) << std::setfill('0')
               << rand() % 1000000;
            card = s5.str();
        }
        cn++;
        if (cn == 5) {
            cn = 0;
        }
        fout << secondName << firstName << thirdName << "," << passportNum << "," << fromPlace << "," << toPlace << "," << dateFrom << "," << dateTo << "," << voyage << "," << placePrice << "," << card << "\n";
    }
    fout.close();
}
