#pragma once

class IComponent {
public:
	virtual ~IComponent() {}
	virtual IComponent *clone()=0;
};

