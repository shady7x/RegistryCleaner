#pragma once

class CClean {
public:
	bool prefetch;
	bool registryUser;
	bool registryStore;
	bool successfully()
	{
		return (this->prefetch && this->registryUser && this->registryStore);
	}
};