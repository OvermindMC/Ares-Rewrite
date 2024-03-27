#include "Debugger.h"

std::string Debugger::name = "Debugger";
bool Debugger::initialized = false;

auto Debugger::init(std::string name) -> void {

	Debugger::name = name;

	if (AllocConsole()) {
		initialized = true;

		FILE* cFile;

		if (freopen_s(&cFile, "CONOUT$", "w", stdout) > 0)
			initialized = false;
		else
			log("Initialized Debugger");
	};

};

auto Debugger::free(void) -> void {

	if (initialized) {
		log("Unitializing Console");
		initialized = false;
		fclose(stdout);
		FreeConsole();
	};

};

auto Debugger::log(const std::string& out) -> void {

	if (initialized) {
		printf("[%s] %s: %s\n", genStamp().c_str(), name.c_str(), out.c_str());
		fflush(stdout);
	};

};

auto Debugger::genStamp(void) -> std::string {

	time_t rawTime;
	struct tm timeInfo;
	char buffer[80];

	time(&rawTime);
	localtime_s(&timeInfo, &rawTime);

	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeInfo);
	return std::string(buffer);

};

auto Debugger::clear(void) -> void {

	if (initialized)
		system("cls");

};