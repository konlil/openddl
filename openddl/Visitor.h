#pragma once

namespace openddl
{
	struct Structure;
	struct Property;
	struct DataArrayList;
	struct DataList;

	struct Visitor
	{
		virtual void visit(Structure & structure) = 0;
		virtual void visit(DataList & data_list) = 0;
		virtual void visit(DataArrayList & data_array_list) = 0;
	};
}