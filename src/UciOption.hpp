//Based on the Stockfish ucioption class.
//https://github.com/mcostalba/Stockfish/blob/master/src/ucioption.h

#ifndef UCIOPTION_HPP_
#define UCIOPTION_HPP_


class UciOption {

public:

UciOption() :
		myDefaultValue(""),
		myCurrentValue(""),
		myType(""),
		min(0), max(0)
{
};

UciOption(std::string defaultValue, std::string type) :
		myDefaultValue(defaultValue),
		myCurrentValue(defaultValue),
		myType(type),
		min(0), max(0)
{
};

UciOption& operator=(const std::string& v )
{
//Blindly update for now

//	if ((myType != "button" && v.empty())
//			|| (myType == "check" && v != "true" && v != "false")
//			|| (myType == "spin" && (stoi(v) < min || stoi(v) > max)))
//		return *this;
//
//	if (myType != "button")
		myCurrentValue = v;

	return *this;
}

UciOption(const std::string v) : myType("string"), min(0), max(0)
{ myDefaultValue = myCurrentValue = v; }

//Everything public for now
std::string myDefaultValue, myCurrentValue, myType;
int min, max;

private:


	//size_t idx;
};

inline std::ostream& operator<<(std::ostream &strm, const UciOption &UciOption) {

	strm << UciOption.myCurrentValue;

	return strm;
}
///// operator<<() is used to print all the options default values in chronological
///// insertion order (the idx field) and in the format defined by the UCI protocol.
//
//std::ostream& operator<<(std::ostream& os, const OptionsMap& om) {
//
//  for (size_t idx = 0; idx < om.size(); ++idx)
//      for (OptionsMap::const_iterator it = om.begin(); it != om.end(); ++it)
//          if (it->second.idx == idx)
//          {
//              const Option& o = it->second;
//              os << "\noption name " << it->first << " type " << o.type;
//
//              if (o.type != "button")
//                  os << " default " << o.defaultValue;
//
//              if (o.type == "spin")
//                  os << " min " << o.min << " max " << o.max;
//
//              break;
//          }
//  return os;
//}


#endif /* UCIOPTION_HPP_ */
