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
		myMin(0), myMax(0)
{
};

	UciOption(std::string defaultValue, std::string type) :
		myDefaultValue(defaultValue),
		myCurrentValue(defaultValue),
		myType(type),
		myMin(0), myMax(0)
	{
	};

	UciOption(std::string defaultValue, std::string type, int min, int max) :
		myDefaultValue(defaultValue),
		myCurrentValue(defaultValue),
		myType(type),
		myMin(min), myMax(max)
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

	UciOption(const std::string v) : myType("string"), myMin(0), myMax(0)
	{ myDefaultValue = myCurrentValue = v; }

	const std::string& getCurrentValue() const
	{
		return myCurrentValue;
	}

	void setCurrentValue(const std::string& currentValue)
	{
		myCurrentValue = currentValue;
	}

	const std::string& getDefaultValue() const
	{
		return myDefaultValue;
	}

	void setDefaultValue(const std::string& defaultValue)
	{
		myDefaultValue = defaultValue;
	}

	const std::string& getType() const
	{
		return myType;
	}

	void setType(const std::string& type)
	{
		myType = type;
	}

	int getMax() const
	{
		return myMax;
	}

	void setMax(int max)
	{
		myMax = max;
	}

	int getMin() const
	{
		return myMin;
	}

	void setMin(int min)
	{
		myMin = min;
	}

private:
	int myMin, myMax;
	std::string myDefaultValue, myCurrentValue, myType;


	//size_t idx;
};

inline std::ostream& operator<<(std::ostream &strm, const UciOption &UciOption) {

	strm << UciOption.getCurrentValue();

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
