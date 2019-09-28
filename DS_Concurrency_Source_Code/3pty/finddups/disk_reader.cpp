#include "disk_reader.h"

disk_reader::disk_reader(int max)
	: max_readers(std::max(max, 1)) {}

int disk_reader::read(std::ifstream& infile, char *buffer, int buffer_size) {
	int read_count = 0;

	std::unique_lock<std::mutex> read_guard(read_lock);
	reader_available.wait(read_guard, [this] {
		return current_readers < max_readers;
	});

	// RAII management of current_readers
	reader_counter counter(this);
	read_guard.unlock();

	if(infile.good()) {
		infile.read(buffer, buffer_size);
		read_count = static_cast<int>(infile.gcount());
	}

	return read_count;
}
