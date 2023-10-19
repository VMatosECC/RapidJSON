#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace std;
// ------------------------------------------------------------------------------
// We use RadipJson to serialize and deserialize a vector of Person objects
// The Person class is a simple class with two data members: name and age
// RapidJson is a SAX-style parser. It does not create a DOM tree in memory.
// Instead, it parses the JSON string sequentially and generates events.
// The events are handled by the user-defined event handler.
// ------------------------------------------------------------------------------
// RAPIDJASON FEATURES
// - RapidJson is a header-only library. No need to link with a library.
// - It is a C++ library and uses C++11 features.
// - RapidJson is a very fast library (It is faster than Boost and Qt)
// - RapidJson is a self-contained library. It does not depend on any other library.
// - It occupies very small memory.  
// - Documentation: http://rapidjson.org/
// - Download from: https://github.com/Tencent/rapidjson/
// ------------------------------------------------------------------------------


class Person {
public:  //Lazy definition 
    string name;
    int    age;
    Person(string nameVal = "na", int ageVal = 0) { name = nameVal; age = ageVal; }
};


// Prototypes ---------------------------------------------------------------------
string EncodePersonsToJson(const vector<Person>& persons);
vector<Person> DecodeJsonToPersons(const string& json);

//----------------------------------------------------------------------------------
int main() {
    // Create some Person objects 
    vector<Person> persons = {
        Person("Homer", 39),
        Person("Bart", 10),
        Person("Lisa", 9),
    };


    // Transform the vector<Person> container to JSON format (SAX style)
    string encodedJson = EncodePersonsToJson(persons);
    cout << "\n EncodedJson: \n\t" << encodedJson << endl;

    // Save the JSON formatted data to a disk text-file
    fstream fout("c:/temp/persons.json", ios::out);
    fout << encodedJson;
    fout.close();

    // Read the JSON formatted data from the disk text-file
    fstream fin("c:/temp/persons.json", ios::in);
    getline(fin, encodedJson);

    // Decode the JSON formatted data back into a vector of Person objects
    vector<Person> decodedPersons = DecodeJsonToPersons(encodedJson);

    // Print the decoded Person objects
    cout << "\n Decoded Json string:\n";
    for (const Person& personObj : decodedPersons) {
        std::cout << "\tPerson [Name: " << personObj.name << ", Age: " << personObj.age << "]\n";
    }

    
}

// ------------------------------------------------------------------------------
// Function to encode a vector of Person objects to JSON
// You have to 'manually' encode the object (SAX style), one element at the time.
// ------------------------------------------------------------------------------
string EncodePersonsToJson(const vector<Person>& persons) {

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);


    writer.StartArray();

    for (const Person& person : persons) {
        writer.StartObject();
        writer.Key("name");
        writer.String(person.name.c_str());
        writer.Key("age");
        writer.Int(person.age);
        writer.EndObject();
    }

    writer.EndArray();

    return buffer.GetString();
}
// ------------------------------------------------------------------------------
// Function to decode JSON into a vector of Person objects
// ------------------------------------------------------------------------------
vector<Person> DecodeJsonToPersons(const string& json) {
    vector<Person> persons;

    // sequentially parse and decode the Json string having the structure
    // Start-Array, Start-Object, Object, End-Object, ... , End-Array
    // and the Objects are made of pairs <key,value> holding name and age.
    rapidjson::Document document;
    document.Parse(json.c_str());

    //verify the string represents a repeating-group
    if (!document.IsArray()) {
        cerr << "JSON is not an array" << endl;
        return persons;
    }

    //Extract one cell at-the-time. Each cell is a Person object
    for (rapidjson::SizeType i = 0; i < document.Size(); ++i) {

        const rapidjson::Value& personObject = document[i];
        //Make sure the object holds the "name" and "age" members
        if (personObject.IsObject()
            && personObject.HasMember("name") && personObject.HasMember("age")) {
            //next two statements retrieve the name and age values
            const rapidjson::Value& nameValue = personObject["name"];
            const rapidjson::Value& ageValue = personObject["age"];
            //if the types agree with those of Person(string, int) create the object 
            if (nameValue.IsString() && ageValue.IsInt()) {
                Person person;
                person.name = nameValue.GetString();
                person.age = ageValue.GetInt();
                persons.push_back(person);
            }
            else {
                cerr << "Invalid JSON format for a person object" << endl;
            }
        }
        else {
            cerr << "Invalid JSON format for a person object" << endl;
        }
    }

    return persons;
}