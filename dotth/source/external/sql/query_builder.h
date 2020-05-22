#ifndef __QUERY_BUILDER__
#define __QUERY_BUILDER__

#include <list>
#include <string>

template<typename query_builder, typename query>
struct builtup_type {
	static query_builder get_builder();
	static query get_query();
	typedef decltype (get_builder().build(get_query())) type;
};

struct base_query {
	base_query& operator >> (base_query query)
	{
		return *this;
	}
};

struct select_query : public base_query {
};

struct insert_query : public base_query {
};

struct delete_query : public base_query {
};

struct update_query : public base_query {
};

namespace details
{
	struct builtup_type 
	{
	};
}

namespace SQL
{
	class QUERY
	{
	public:
		explicit QUERY(void) {}
		virtual ~QUERY(void) {}
		virtual const std::string& build(void) = 0;
	protected:
		std::string _result;
	private:
		QUERY(const QUERY& m) = delete;
		QUERY& operator =(const QUERY& data) = delete;

		template <typename builder>
		typename details::builtup_type operator >>(builder _builder)
		{
			return _builder.build(*this);
		}
	};
} // namespace SQL


/*
query::select("asd, asd, asdj, asjdidjf") >>
query::where("sdj >= 11 && efji 
*/




#endif // __QUERY_BUILDER__