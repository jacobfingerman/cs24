#include "GenePool.h"

// GenePool Member Functions

void GenePool::clearRec() {
    for (auto itr = data.begin(); itr != data.end(); ++itr) {
        delete itr->second;
    }
}

GenePool::GenePool(std::istream& stream) {
    std::string line;
    while (getline(stream, line)) {
        if (line[0] != '#' && line[0] != 0) {
            // Oceanus male    Gaia    Uranus

            size_t inds[3];
            inds[0] = line.find(9);
            inds[1] = line.find(9, inds[0] + 1);
            inds[2] = line.find(9, inds[1] + 1);

            Person* entry = new Person(
                line.substr(0, inds[0]),
                line.substr(inds[0] + 1, inds[1] - inds[0] - 1),
                data[line.substr(inds[1] + 1, inds[2] - inds[1] - 1)],
                data[line.substr(inds[2] + 1, line.length() - inds[2] - 1)]
            );

            data[entry->name()] = entry;

            if (entry->father()) {
                Person::ParentTree* newC;
                newC = entry->father()->addChild(entry);

                if (newC && entry->mother()) entry->mother()->pushTree(newC);
            }
            else if (entry->mother()) entry->mother()->addChild(entry);
        }
    }
}

GenePool::~GenePool() {
    clearRec();
}


Person* GenePool::find(const std::string& name) const {
    auto output = data.find(name);
    if (output == data.end()) return nullptr;
    else return output->second;
}




