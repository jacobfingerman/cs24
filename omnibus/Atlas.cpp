#include "Atlas.h"


Atlas::Atlas(std::istream& stream) {
	// Creates atlas with stream
	mapping = Mapper();
	std::string line;

	while (getline(stream, line)) {
		LOOP:
		std::istringstream words(line);
		std::string word1;
		words >> word1;

		if (word1 == "BUS:" || word1 == "TRAIN:") {

			//Track line name until next line
			std::string type = word1;
			std::string lineName = "";
			words >> std::ws >> lineName;
			
			while (words >> std::ws >> word1) { lineName += " " + word1; }

			// Skip comments 
			while (getline(stream, line) && line[0] != '-') {}

			// Process first station line
			std::string currTime;
			std::string currName;
			std::istringstream words(line);
			words >> currTime >> currTime >> std::ws >> currName;
			while (words >> word1) { currName += " " + word1; }

			mapping.add(currName);


			std::string lastTime;
			std::string lastName;
			// Loops through remaining stations in this line
			while (getline(stream, line) && line[0] == '-') {
				lastTime = currTime;
				lastName = currName;

				std::istringstream words(line);
				words >> currTime >> currTime >> std::ws >> currName;
				while (words >> word1) { currName += " " + word1; }
				int dist = (type == "BUS:") ? 0 : std::stoi(currTime) - std::stoi(lastTime);
				mapping.insert(currName, lastName, lineName, dist);
			}
			goto LOOP;
		}

		// Check lines until it finds bus or train
	
	}

}

Atlas::~Atlas() {}

Atlas* Atlas::create(std::istream& stream) {
  // This default implementation will probably do what you want.
  // If you use a different constructor, you'll need to change it.
  return new Atlas(stream);
}


Trip Atlas::route(const std::string& src, const std::string& dst) {
	// Finds shortest route between stations

	size_t statCount = mapping.size();
	std::vector<std::pair<int, Station::Edge>> dist(statCount, {MAXINT, Station::Edge()});
	Heap heap(800000);
	paired source = mapping.find(src);
	paired dest = mapping.find(dst);

	// Input validation
	if (source == mapping.end() || dest == mapping.end()) {
		throw std::runtime_error("No route.");
	}

	// Add first vertex to heap
	Entry curr(&source->second, 0);
	heap.push(&source->second, 0);
	dist[source->second.id].first = 0;
	
	while (heap.count()) { // Loop through edges

		Station* current = heap.pop().station;

		if (current == &dest->second) break; // Shortest route has been found

		for (auto it = current->edges.begin(); it < current->edges.end(); ++it) {
			Station* next = it->connection;
			int weight = it->weight;

			// Ignore unless vertex has a shorter route
			if (dist[next->id].first > dist[current->id].first + weight) {
				// Update shortest path array
				dist[next->id].first = dist[current->id].first + weight;
				dist[next->id].second = *it;
				dist[next->id].second.connection = current;

				heap.push(next, dist[next->id].first);
			}
		}
	}
	
	// Disjoint stations case
	if (!dist[dest->second.id].second.connection) throw std::runtime_error("No route.");

	
	Trip output;
	output.start = source->first;
	output.legs.reserve(statCount);

	size_t currInd = dest->second.id;
	size_t sourceInd = source->second.id;

	// Pop heap to get backwards route
	while (currInd != sourceInd) {
		std::string currLine = dist[currInd].second.line;

		Trip::Leg leg;
		leg.line = currLine;
		leg.stop = mapping.find(currInd);

		while (currInd != sourceInd && dist[currInd].second.line == currLine) { 
			currInd = dist[currInd].second.connection->id; // Skip same line stations
		}

		output.legs.push_back(leg);	// Add completed leg
	}

	// Fixes backwards trip being backwards
	std::reverse(output.legs.begin(), output.legs.end());

	return output;
}