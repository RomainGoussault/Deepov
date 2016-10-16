/*
	Deepov, a UCI chess playing engine.

	Copyright (c) 20014-2016 Romain Goussault, Navid Hedjazian

    Deepov is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Deepov is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Deepov.  If not, see <http://www.gnu.org/licenses/>.
*/

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
	std::string myDefaultValue, myCurrentValue, myType;
	int myMin, myMax;


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
