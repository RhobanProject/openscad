#pragma once

#include "node.h"
#include "visitor.h"
#include <string>

class DumpNode : public AbstractNode
{
public:
	DumpNode(const ModuleInstantiation *mi) : AbstractNode(mi) { }
  virtual Response accept(class State &state, Visitor &visitor) const {
		return visitor.visit(state, *this);
	}
	virtual std::string toString() const;
	virtual std::string name() const { return "dump"; }
};

void dump_nodes(AbstractNode *node);
