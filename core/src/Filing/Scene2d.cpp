#include <iostream>
#include <memory>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>

#include "Scene2d.h"
#include "Exception.h"
#include "Debug.h"
#include "JsonIO.h"

namespace ample::filing
{

Scene2d::Scene2d(const std::string &nameFile)
        : ample::physics::WorldLayer2d {{0.0, 0.0}, 0.0, 0.0, 0.5}
{
    DEBUG("load from json file");
    std::string fileStr = openJSONfile(nameFile);

    rapidjson::Document config;
    config.Parse(fileStr.c_str());

    const rapidjson::Value &data = config["data"];

    size_t cnt = 0;
    _objs.resize(data.Size());
    for (rapidjson::Value::ConstValueIterator itr = data.Begin(); itr != data.End(); ++itr)
    {
        const rapidjson::Value &attribute = *itr;
        rapidjson::StringBuffer sb;
        rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
        attribute.Accept(writer);
        std::string str = sb.GetString();

        rapidjson::Document doc;
        doc.Parse(str.c_str());

        JsonIO editor(str);
        std::string name = editor.read<std::string>("name");

        if (name == "GraphicalObject2d")
        {
            ample::graphics::GraphicalObject2d obj(editor);
            _objs[cnt] = std::make_shared<ample::graphics::GraphicalObject>(obj);
            addObject(*_objs[cnt]);
            DEBUG("add GraphicalObject2d");
        }
        std::string id = editor.read<std::string>("id");
        _storage[id] = _objs[cnt];
        cnt++;
    }
}

void Scene2d::saveScene(const std::string &nameFile)
{
    std::ofstream outFile(nameFile);

    rapidjson::Document doc;
    doc.SetObject();

    rapidjson::Value array(rapidjson::Type::kArrayType);
    for (size_t i = 0; i < _objs.size(); i++)
    {
        rapidjson::Document docObj(&doc.GetAllocator());
        docObj.SetObject();

        ample::filing::JsonIO io("");
        if (typeid(*_objs[i]) == typeid(ample::graphics::GraphicalObject2d))
        {
//            _objs[i]->dump(io);
//            std::string str = io.getJSONstring();
//            docObj.Parse(str.c_str());
//            docObj.AddMember("class", "GraphicalObject2d", docObj.GetAllocator());
        }
        array.PushBack(docObj, doc.GetAllocator());
    }
    doc.AddMember("array", array, doc.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    std::string str(buffer.GetString(), buffer.GetSize());
    outFile << str << '\n';
    outFile.close();
}

ample::graphics::GraphicalObject &Scene2d::getElementById(const std::string &id)
{
    return *_storage[id];
}
} // namespace ample::filing
