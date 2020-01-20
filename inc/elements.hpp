/*
    Copyright (c) 2020 Harrison Wade, aka "RigoLigo RLC"

    This file is part of LC2KiCad.

    LC2KiCad is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as 
    published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version.

    LC2KiCad is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with LC2KiCad. If not, see <https://www.gnu.org/licenses/>.
*/
  
#ifndef LC2KICAD_ELEMENTS
  #define LC2KICAD_ELEMENTS

  #include <include.hpp>
  #include <consts.hpp>
  #include <rapidjson.hpp>

  using std::vector;
  using std::fstream;
  using std::string;
  //using rapidjson::Value;

  namespace lc2kicad
  {
    class coordinates
    {
      public:
        float X;
        float Y;

        coordinates operator+(coordinates coord)
          { coordinates ret; ret.X = this->X + coord.X; ret.Y = this->Y + coord.Y; return ret; }
        coordinates operator-(coordinates coord)
          { coordinates ret; ret.X = this->X - coord.X; ret.Y = this->Y - coord.Y; return ret; }
        coordinates operator*(coordinates coord)
          { coordinates ret; ret.X = this->X * coord.X; ret.Y = this->Y * coord.Y; return ret; }
        coordinates operator/(coordinates coord)
          { coordinates ret; ret.X = this->X / coord.X; ret.Y = this->Y / coord.Y; return ret; }
        coordinates operator+(float n)
          { coordinates ret; ret.X = this->X + n; ret.Y = this->Y + n; return ret; }
        coordinates operator*(float n)
          { coordinates ret; ret.X = this->X * n; ret.Y = this->Y * n; return ret; }
    };

    typedef coordinates sizeXY;

    struct PCBElements
    {

        bool isVisible;

        bool getVisibility() { return isVisible; };
        void setVisibility(bool visibility) { isVisible = visibility; };
        virtual string outputKiCadFormat(string &convArgs, char* &indent) { return string("default"); };
        //string outputKiCadFormat();
    };

    enum class PCBPadShape : int { circle = 0, oval = 1, rectangle = 2, polygon = 3 };
    enum class PCBPadType : int { top = 0, bottom = 1, through = 2, noplating = 3 };
    enum class PCBHoleShape : int { circle = 0, slot = 1 };

    struct PCB_Pad : public PCBElements
    {

        PCBPadShape padShape;
        PCBPadType padType;
        PCBHoleShape holeShape;
        int orientation;
        coordinates padCoordinates;
        sizeXY padSize, holeSize;
        string netName, pinNumber;

        string outputKiCadFormat(string &convArgs, char* &indent);
        vector<coordinates> shapePolygonPoints;
        /*void setPadCoordinate(float X, float Y) { padCoordinates.X = X; padCoordinates.Y = Y; };
          void setPadSize(float X, float Y) { padSize.X = X; padSize.Y = Y; };
          void setHoleSize(float X, float Y) { holeSize.X = X; holeSize.Y = Y; };
          void setPadRotation(float rotation) { orientation = rotation; };
          void setPadShape(int shape) { padShape = shape; };
          void setPadType(int type) { padType = type; };
          void setHoleShape(int shape) { holeShape = shape; };

          const coordinates &getPadCoordinate() { return padCoordinates; };
          const sizeXY &setPadSize() { return padSize; };
          const sizeXY &setHoleSize() { return holeSize; };
          float getPadRotation() { return orientation; };
          int getPadShape() { return padShape; };
          int getPadType() { return padType; };
          int getHoleShape() { return holeShape; };*/
    };

    struct PCB_Track : public PCBElements
    {
        int  width, layerKiCad;
        vector<coordinates> trackPoints;
        string netName;
    };

    struct PCB_Via : public PCBElements
    {
        int viaSize, drillSize;
        coordinates viaCoordinates;
        string netName;

        string outputKiCadFormat(string &convArgs, char* &indent);
    };
  }
#endif
