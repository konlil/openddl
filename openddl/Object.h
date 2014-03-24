#pragma once
#include <string>
#include <functional>

namespace openddl
{
	//Helper templates
	template <typename T>
	struct is_openddl_object
	{
		static const bool value = std::is_same<DataArray, T>::value || std::is_same<DataList, T>::value || std::is_same<Structure, T>::value;
	};
	
	struct Visitor;
	struct Property;
	//Internal handle object
	struct Object
	{
		Object();
	protected:
		friend struct Tree;
		Object(Tree * t, const unsigned int i);
		Tree * tree;
		const unsigned int index;
	};
	struct Property : Object
	{
		Property();
	private:
		friend struct Tree;
		Property(const Object & o);
	};
	struct Structure : Object
	{
		Structure();
		void visit_children(Visitor & v);
		void visit_properties(std::function<void(const Property&)> visitor);

		bool has_name();

		const std::string & name();
		const std::string & identifier();

		unsigned int has_properties();
		unsigned int has_children();

	private:
		friend struct Tree;
		Structure(const Object & o);
	};
	struct DataList : Object
	{
		DataList();
	private:
		friend struct Tree;
		DataList(const Object & o);
	};
	struct DataArrayList : Object
	{
		DataArrayList();
	private:
		friend struct Tree;
		DataArrayList(const Object & o);
	};
}