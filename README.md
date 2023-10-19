# RapidJSON
This app uses RapidJason to serialize a vector of Person objects.
Each Person holds name:string and age:int
The serialized string is written to the disk file "c:/temp/persons.json"

------------------------------------------------------------------------------
RapidJson is a SAX-style parser. It does not create a DOM tree in memory.
Instead, it parses the JSON string sequentially and generates events.
The events are handled by the user-defined event handler.

RAPIDJASON FEATURES
- RapidJson is a header-only C++ library. No need to link with a library.
- It is a very fast library (faster than Boost and Qt)
- It is self-contained and does not depend on any other library.
- It occupies a very small memory.  
- Documentation: http://rapidjson.org/
- Download from: https://github.com/Tencent/rapidjson/

