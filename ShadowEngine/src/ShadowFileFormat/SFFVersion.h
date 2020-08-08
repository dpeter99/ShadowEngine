#pragma once

struct SFFVersion {
public:
	int mayor;
	int minor;
	int patch;

	bool invalid;

	SFFVersion(int ma, int mi, int pa)
	{
		this->mayor = ma;
		this->minor = mi;
		this->patch = pa;

		if (ma >= 0 && mi >= 0 && pa >= 0) {
			this->invalid = false;
		}
		else
		{
			invalid = true;
		}
	}
};