
const double ASPECT_RATIO = 1.653;

const char* const authorName = "Scott Meyers";

inline int non_std_max(int a, int b) { return a > b ? a : b; }

// generic
template<class T>
inline const T& non_std_max(const T& a, const T& b)
{
	return a > b : a ? b;
}
