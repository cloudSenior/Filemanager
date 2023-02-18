#include <iostream>
#include <map>
#include "contoller.hh"










int main() {
	using namespace std;

	setlocale(LC_ALL, "Russian");

	FAController controller;
	std::string rootDirect = controller.RootFilterPath();

	controller.uploadedData();

	if (rootDirect == "")
	{
		cout << "В конфиге у вас не найдена строка [#rootfilter: ] или [modules: ]" << endl;
		cin.get();
		return -1;
	}

	
	
	for (auto i : filesystem::directory_iterator(rootDirect))
	{
		std::string format   = i.path().extension().string();
		std::string full     = i.path().filename().string();

		if (controller.data[format] != "")
		{
			try {
				std::filesystem::copy(rootDirect + "\\" + full, controller.data[format] + "\\" + full);
				std::filesystem::remove(rootDirect + "\\" + full);
			}
			catch (std::filesystem::filesystem_error& e) {
				std::cout << e.what() << '\n';
			}
		}
	}


	return EXIT_SUCCESS;
}

