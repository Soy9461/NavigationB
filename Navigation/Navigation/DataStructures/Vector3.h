#ifndef _VECTOR3_H_
#define _VECTOR3_H_

// 随便写了个简单的三维坐标模板练练手
// 如果使用没问题无视即可

template<typename T>
struct Vec3_tpl
{
	T x;
	T y;
	T z;

	Vec3_tpl<T>()
	:	x(T())
	,	y(T())
	,	z(T()){}

	Vec3_tpl<T>(const Vec3_tpl<T> &rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
	}

	Vec3_tpl<T>(T _x, T _y, T _z)
	:	x(_x)
	,	y(_y)
	,	z(_z){}

	Vec3_tpl<T> &operator+=(const Vec3_tpl<T> &rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	Vec3_tpl<T> operator+(const Vec3_tpl<T> &rhs)
	{
		Vec3_tpl<T> temp(*this);
		temp += rhs;
		return temp; 
	}

	Vec3_tpl<T> operator+(const Vec3_tpl<T> &rhs) const
	{
		Vec3_tpl<T> temp(*this);
		temp += rhs;
		return temp; 
	}


	Vec3_tpl<T> &operator-=(const Vec3_tpl<T> &rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	Vec3_tpl<T> operator-(const Vec3_tpl<T> &rhs)
	{
		Vec3_tpl<T> temp(*this);
		temp -= rhs;
		return temp; 
	}

	Vec3_tpl<T> operator-(const Vec3_tpl<T> &rhs) const
	{
		Vec3_tpl<T> temp(*this);
		temp -= rhs;
		return temp; 
	}

	Vec3_tpl<T> &operator=(const Vec3_tpl<T> &rhs)
	{
		if(this == &rhs)
			return *this;
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}

	template<typename T2>
	Vec3_tpl<T> &operator=(const Vec3_tpl<T2> &rhs)
	{
		if(this == &rhs)
			return *this;
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}

	T GetLength(){return sqrt(x*x + y*y + z*z);}
	T GetLengthSquard(){return x*x + y*y + z*z;}
	T Getlength2D(){return sqrt(x*x + y*y);}
	T GetlengthSquard2D(){return x*x + y*y;}
};


typedef Vec3_tpl<double> Vec3;
typedef Vec3_tpl<float> fVec3;
typedef Vec3_tpl<int> iVec3;


#endif