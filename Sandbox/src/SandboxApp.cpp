#include <GES.h>

class Sandbox : public GES::Application
{
public:
	Sandbox()
	{
	}

	~Sandbox()
	{
	}
};

GES::Application *GES::CreateApplication()
{
	return new Sandbox();
}
