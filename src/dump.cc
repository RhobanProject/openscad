/*
 *  OpenSCAD (www.openscad.org)
 *  Copyright (C) 2009-2011 Clifford Wolf <clifford@clifford.at> and
 *                          Marius Kintel <marius@kintel.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  As a special exception, you have permission to link this program
 *  with the CGAL library and distribute executables, as long as you
 *  follow the requirements of the GNU GPL in regard to all of the
 *  software in the executable aside from CGAL.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include "dumpnode.h"
#include "module.h"
#include "evalcontext.h"
#include "builtin.h"
#include "polyset.h"
#include "dumpnode.h"
#include "transformnode.h"

#include <sstream>
#include <boost/assign/std/vector.hpp>
using namespace boost::assign; // bring 'operator+=()' into scope

std::string DumpNode::toString() const
{
	std::stringstream stream;

	stream << this->name();

	return stream.str();
}

static void dump(AbstractNode *node, int *id, Transform3d matrix = Transform3d::Identity())
{
    DumpNode *dumpnode = dynamic_cast<DumpNode*>(node);
    if (dumpnode) {
        std::cout << "Dump point " << (*id)++ << ": ";
        Matrix4d m = matrix.matrix();
        std::cout << ""
           "[[" << m(0, 0) << "," << m(0, 1) << "," << m(0, 2) << "," << m(0,3) << "]," <<
            "[" << m(1, 0) << "," << m(1, 1) << "," << m(1, 2) << "," << m(1,3) << "]," <<
            "[" << m(2, 0) << "," << m(2, 1) << "," << m(2, 2) << "," << m(2,3) << "]," <<
            "[" << m(3, 0) << "," << m(3, 1) << "," << m(3, 2) << "," << m(3,3) << "]]" 
            << std::endl;
    } else {
        TransformNode *transformnode = dynamic_cast<TransformNode*>(node);
        if (transformnode) {
            matrix = matrix * transformnode->matrix;
        }
        const std::vector<AbstractNode*> children = node->getChildren();
        for (int i=0; i<children.size(); i++) {
            dump(children[i], id, matrix);
        }
    }
}

void dump_nodes(AbstractNode *node)
{
    int id = 0;
    dump(node, &id);
}
