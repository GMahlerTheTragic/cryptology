#ifndef CRYPTOLOGY_ANALYSIS_FREQUENCIES_HPP_
#define CRYPTOLOGY_ANALYSIS_FREQUENCIES_HPP_

#include <map>

const map<std::string, double> ENGLISH_FREQUENCIES{
    {"A", 0.0804},
    {"B", 0.0154},
    {"C", 0.0306},
    {"D", 0.0399},
    {"E", 0.1251},
    {"F", 0.0230},
    {"G", 0.0196},
    {"H", 0.0549},
    {"I", 0.0726},
    {"J", 0.0016},
    {"K", 0.0067},
    {"L", 0.0414},
    {"M", 0.0253},
    {"N", 0.0709},
    {"O", 0.0760},
    {"P", 0.0200},
    {"Q", 0.0011},
    {"R", 0.0612},
    {"S", 0.0654},
    {"T", 0.0925},
    {"U", 0.0271},
    {"V", 0.0099},
    {"W", 0.0192},
    {"X", 0.0019},
    {"Y", 0.0173},
    {"Z", 0.0009}
};
const map<std::string, double> ENGLISH_BIGRAM_FREQUENCIES{
    {"TH", 0.0356},
    {"HE", 0.0307},
    {"IN", 0.0243},
    {"ER", 0.0205},
    {"AN", 0.0199},
    {"RE", 0.0185},
    {"ON", 0.0176},
    {"AT", 0.0149},
    {"EN", 0.0145},
    {"ND", 0.0135},
    {"TI", 0.0134},
    {"ES", 0.0134},
    {"OR", 0.0128},
    {"TE", 0.0120},
    {"OF", 0.0117},
    {"ED", 0.0117},
    {"IS", 0.0113},
    {"IT", 0.0112},
    {"AL", 0.0109},
    {"AR", 0.0107},
    {"ST", 0.0105},
    {"TO", 0.0104},
    {"NT", 0.0104},
    {"NG", 0.0095},
    {"SE", 0.0093},
    {"HA", 0.0093},
    {"AS", 0.0087},
    {"OU", 0.0087},
    {"IO", 0.0083},
    {"LE", 0.0083},
    {"VE", 0.0083},
    {"CO", 0.0079},
    {"ME", 0.0079},
    {"DE", 0.0076},
    {"HI", 0.0076},
    {"RI", 0.0073},
    {"RO", 0.0073},
    {"IC", 0.0070},
    {"NE", 0.0069},
    {"EA", 0.0069},
    {"RA", 0.0069},
    {"CE", 0.0065},
    {"LI", 0.0062},
    {"CH", 0.0060},
    {"LL", 0.0058},
    {"BE", 0.0058},
    {"MA", 0.0057},
    {"SI", 0.0055},
    {"OM", 0.0055},
    {"UR", 0.0054},
};

const map<std::string, double> ENGLISH_TRIGRAM_FREQUENCIES{
    {"THE", 0.0353},
    {"ING", 0.0111},
    {"AND", 0.0102},
    {"ION", 0.0075},
    {"TIO", 0.0075},
    {"ENT", 0.0073},
    {"ERE", 0.0069},
    {"HER", 0.0068},
    {"ATE", 0.0066},
    {"VER", 0.0064},
    {"TER", 0.0063},
    {"THA", 0.0062},
    {"ATI", 0.0059},
    {"FOR", 0.0059},
    {"HAT", 0.0055},
    {"ERS", 0.0054},
    {"HIS", 0.0052},
    {"RES", 0.0050},
    {"ILL", 0.0047}
};

const double ENGLISH_INDEX_OF_COINCIDENCE = 0.0687;

const map<std::string, double> GERMAN_FREQUENCIES{
    {"A", 0.0647},
    {"B", 0.0193},
    {"C", 0.0268},
    {"D", 0.0487},
    {"E", 0.1748},
    {"F", 0.0165},
    {"G", 0.0306},
    {"H", 0.0425},
    {"I", 0.0773},
    {"J", 0.0027},
    {"K", 0.0146},
    {"L", 0.0349},
    {"M", 0.0258},
    {"N", 0.0982},
    {"O", 0.0298},
    {"P", 0.0096},
    {"Q", 0.0002},
    {"R", 0.0754},
    {"S", 0.0683},
    {"T", 0.0613},
    {"U", 0.0417},
    {"V", 0.0094},
    {"W", 0.0148},
    {"X", 0.0004},
    {"Y", 0.0008},
    {"Z", 0.0114}
};
const map<std::string, double> GERMAN_BIGRAM_FREQUENCIES{
    {"ER", 0.0409},
    {"EN", 0.0040},
    {"CH", 0.0242},
    {"DE", 0.0227},
    {"EI", 0.0193},
    {"ND", 0.0187},
    {"TE", 0.0185},
    {"IN", 0.0168},
    {"IE", 0.0163},
    {"GE", 0.0147},
    {"ES", 0.0140},
    {"NE", 0.0122},
    {"UN", 0.0119},
    {"ST", 0.0116},
    {"RE", 0.0112},
    {"HE", 0.0102},
    {"AN", 0.0102},
    {"BE", 0.0101},
    {"SE", 0.0099},
    {"NG", 0.0094},
    {"DI", 0.0093},
    {"SC", 0.0089}
};

const map<std::string, double> GERMAN_TRIGRAM_FREQUENCIES{
    {"EIN", 0.0122},
    {"ICH", 0.0111},
    {"NDE", 0.0089},
    {"DIE", 0.0087},
    {"UND", 0.0087},
    {"DER", 0.0086},
    {"CHE", 0.0075},
    {"END", 0.0075},
    {"GEN", 0.0071},
    {"SCH", 0.0066},
    {"CHT", 0.0061},
    {"DEN", 0.0057},
    {"INE", 0.0053},
    {"NGE", 0.0052},
    {"NUN", 0.0048},
    {"UNG", 0.0048},
    {"DAS", 0.0047},
    {"HEN", 0.0047},
    {"IND", 0.0046}
};

const double GERMAN_INDEX_OF_COINCIDENCE = 0.0762061;

#endif