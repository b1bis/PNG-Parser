#include <PNG/Image.hpp>

int main(int argc, char** argv)
{
	PNG::Image france("../asset/france.png", false); // Only load Header
	std::cout << "France : Lenght = " << france.GetLenght() << "; Height = " << france.GetHeight() << std::endl;
	france.LoadImageContent(); // Load image
	std::cout << france.GetContent().At(300, 300) << std::endl;

	return EXIT_SUCCESS;
}