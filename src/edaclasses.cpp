/*
    Copyright (c) 2020 RigoLigoRLC.

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
  
#include <vector>
#include <fstream>
#include <string>
#include <memory>

#include "includes.hpp"
#include "consts.hpp"
#include "lc2kicadcore.hpp"
#include "rapidjson.hpp"
#include "edaclasses.hpp"

using std::vector;
using std::fstream;
using std::string;

namespace lc2kicad
{
  EDADocument::EDADocument()
  {
    jsonParseResult = std::make_shared<rapidjson::Document>();
  }
  
  void EDADocument::addElement(EDAElement*) {} //I wished it to be a pure virtual function but can't do it. UHHH

  EDADocument::~EDADocument()
  {

  }

  EDADocument::EDADocument(const bool useJSONStorage)
  {
    if(useJSONStorage)
      jsonParseResult = std::make_shared<rapidjson::Document>();
  }

  string* EDADocument::deserializeSelf() const { return nullptr; }
  
  EDAElement::~EDAElement()
  {
    
  }

  PCBDocument::PCBDocument(const EDADocument& a)// : EDADocument::EDADocument(true)
  {
    pathToFile = a.pathToFile;
    docInfo = a.docInfo;
    module = a.module;
    jsonParseResult = a.jsonParseResult;
  }
  
  void PCBDocument::addElement(EDAElement* element)
  {
    element->parent = this;
    if(this->module)
      static_cast<PCB_Module*>(this->containedElements[0])->containedElements.push_back(static_cast<PCBElement*>(element));
    else
      this->containedElements.push_back(static_cast<PCBElement*>(element));
  }

  PCBDocument::~PCBDocument() //Destructor
  {
    if(containedElements.size() != 0) //Free memory taken up by elements contained in the document
      for(auto i : containedElements) //Iterate through the vector
        if(!i) //If it's not a NULL or nullptr
          delete i;
  }
  
  SchematicDocument::SchematicDocument(const EDADocument& a)// : EDADocument::EDADocument(true)
  {
    pathToFile = a.pathToFile;
    docInfo = a.docInfo;
    module = a.module;
    jsonParseResult = a.jsonParseResult;
  }

  SchematicDocument::~SchematicDocument() //Destructor
  {
    if(containedElements.size() != 0) //Free memory taken up by elements contained in the document
      for(auto i : containedElements) //Iterate through the vector
        if(!i) //If it's not a NULL or nullptr
          delete i;
  }
  
  string* PCB_Module::deserializeSelf() const { return parent->parent->getDeserializer()->outputPCBModule(*this); }
  string* PCB_Module::deserializeSelf(KiCad_5_Deserializer& deserializer) const { return deserializer.outputPCBModule(*this); }

  string* PCB_Pad::deserializeSelf() const { return parent->parent->getDeserializer()->outputPCBPad(*this); }
  string* PCB_Pad::deserializeSelf(KiCad_5_Deserializer& deserializer) const { return deserializer.outputPCBPad(*this); }

  string* PCB_GraphicalTrack::deserializeSelf() const { return parent->parent->getDeserializer()->outputPCBGraphicalTrack(*this); }
  string* PCB_GraphicalTrack::deserializeSelf(KiCad_5_Deserializer& deserializer) const { return deserializer.outputPCBGraphicalTrack(*this); }

  string* PCB_CopperTrack::deserializeSelf() const { return parent->parent->getDeserializer()->outputPCBCopperTrack(*this); }
  string* PCB_CopperTrack::deserializeSelf(KiCad_5_Deserializer& deserializer) const { return deserializer.outputPCBCopperTrack(*this); }

  string* PCB_Hole::deserializeSelf() const { return parent->parent->getDeserializer()->outputPCBHole(*this); }
  string* PCB_Hole::deserializeSelf(KiCad_5_Deserializer& deserializer) const { return deserializer.outputPCBHole(*this); }

  string* PCB_Via::deserializeSelf() const { return parent->parent->getDeserializer()->outputPCBVia(*this); }
  string* PCB_Via::deserializeSelf(KiCad_5_Deserializer& deserializer) const { return deserializer.outputPCBVia(*this); }

  string* PCB_SolidRegion::deserializeSelf() const { return parent->parent->getDeserializer()->outputPCBSolidRegion(*this); }
  string* PCB_SolidRegion::deserializeSelf(KiCad_5_Deserializer& deserializer) const { return deserializer.outputPCBSolidRegion(*this); }
  
  string* PCB_FloodFill::deserializeSelf() const { return parent->parent->getDeserializer()->outputPCBFloodFill(*this); }
  string* PCB_FloodFill::deserializeSelf(KiCad_5_Deserializer& deserializer) const { return deserializer.outputPCBFloodFill(*this); }

  string* PCB_GraphicalCircle::deserializeSelf() const { return parent->parent->getDeserializer()->outputPCBGraphicalCircle(*this); }
  string* PCB_GraphicalCircle::deserializeSelf(KiCad_5_Deserializer& deserializer) const { return deserializer.outputPCBGraphicalCircle(*this); }

  string* PCB_CopperCircle::deserializeSelf() const { return parent->parent->getDeserializer()->outputPCBCopperCircle(*this); }
  string* PCB_CopperCircle::deserializeSelf(KiCad_5_Deserializer& deserializer) const { return deserializer.outputPCBCopperCircle(*this); }

  string* PCB_Rect::deserializeSelf() const { return parent->parent->getDeserializer()->outputPCBRect(*this); }
  string* PCB_Rect::deserializeSelf(KiCad_5_Deserializer& deserializer) const { return deserializer.outputPCBRect(*this); }

  string* PCB_GraphicalArc::deserializeSelf() const { return parent->parent->getDeserializer()->outputPCBGraphicalArc(*this); }
  string* PCB_GraphicalArc::deserializeSelf(KiCad_5_Deserializer& deserializer) const { return deserializer.outputPCBGraphicalArc(*this); }

  string* PCB_CopperArc::deserializeSelf() const { return parent->parent->getDeserializer()->outputPCBCopperArc(*this); }
  string* PCB_CopperArc::deserializeSelf(KiCad_5_Deserializer& deserializer) const { return deserializer.outputPCBCopperArc(*this); }

  string* Schematic_Module::deserializeSelf() const { return parent->parent->getDeserializer()->outputSchModule(*this); }
  string* Schematic_Module::deserializeSelf(KiCad_5_Deserializer& deserializer) const { return deserializer.outputSchModule(*this); }

  string* Schematic_Pin::deserializeSelf() const { return parent->parent->getDeserializer()->outputSchPin(*this); }
  string* Schematic_Pin::deserializeSelf(KiCad_5_Deserializer& deserializer) const { return deserializer.outputSchPin(*this); }
  
  string* Schematic_Polyline::deserializeSelf() const { return parent->parent->getDeserializer()->outputSchPolyline(*this); }
  string* Schematic_Polyline::deserializeSelf(KiCad_5_Deserializer& deserializer) const { return deserializer.outputSchPolyline(*this); }
  
  string* Schematic_Rect::deserializeSelf() const { return parent->parent->getDeserializer()->outputSchRect(*this); }
  string* Schematic_Rect::deserializeSelf(KiCad_5_Deserializer& deserializer) const { return deserializer.outputSchRect(*this); }
  
  string* Schematic_Polygon::deserializeSelf() const { return parent->parent->getDeserializer()->outputSchPolygon(*this); }
  string* Schematic_Polygon::deserializeSelf(KiCad_5_Deserializer& deserializer) const { return deserializer.outputSchPolygon(*this); }
  
  string* Schematic_Text::deserializeSelf() const { return parent->parent->getDeserializer()->outputSchText(*this); }
  string* Schematic_Text::deserializeSelf(KiCad_5_Deserializer& deserializer) const { return deserializer.outputSchText(*this); }
}
