#ifndef __VECTOR2_H__
#define __VECTOR2_H__

template <typename T>
class Vector2 {

public:
	T x;
	T y;

	Vector2() : x(0), y(0) {}
	Vector2(T _x, T _y) : x(_x), y(_y) {}
	Vector2(T const coords[2]) : x(coords[0]), y(coords[1]) {}
	Vector2(Vector2<T> const &v) : x(v.x), y(v.y) {}

	~Vector2() = default;

	/*
	* ## Instance Methods
	*/

	// Get this vectors components as a const T array.
	const T* ToArray() {
		return &x;
	}
	// Sets the x and y component of the vector
	void SetCoords(T _x, T _y) {
		x = _x;
		y = _y;
	}

	// Get the length of this vector
	T Length() {
		return sqrt((x*x) + (y*y));
	}
	// Normalize this vector
	void Normalize() {
		double const len = Length();
		Div(len);
	}
	// Get a nomalized copy of this vector.
	Vector2<T> normalized() {
		auto result = *this;
		result.Normalize();
		return result;
	}

	// Adds provided Vector2 of same type onto this.
	/*void Add (Vector2<T> const &v) {
	x += v.x;
	y += v.y;
	}*/
	// Adds provided double Vector2 onto this.
	void Add (Vector2<double> const &v) {
		x += v.x;
		y += v.y;
	}
	// Adds provided ineger Vector2 onto this.
	void Add (Vector2<int> const &v) {
		x += v.x;
		y += v.y;
	}
	// Adds provided float Vector2 onto this.
	void Add (Vector2<float> const &v) {
		x += v.x;
		y += v.y;
	}
	// Functions for subtracting Vector's
	void Sub (Vector2<T> const &v) {
		x -= v.x;
		y -= v.y;
	}
	// Scale this vector by a scalar
	void Mult (T const scalar) {
		x *= scalar;
		y *= scalar;
	}
	// Scale this vector by a scalar.
	void Div (T const scalar) {
		x /= scalar;
		y /= scalar;
	}

	/*
	* ## Static Methods
	*/

	// Get the dot product of two vectors
	static double Dot(Vector2<T> const & lhs, Vector2<T> const & rhs) {
		return ((lhs.x * rhs.x) + (lhs.y * rhs.y));
	}
	// Adds the vectors and retern's as a new one.
	static Vector2<T> Add (Vector2<T> const &lhs, Vector2<T> const &rhs) {
		Vector2 result (lhs.x + rhs.x, lhs.y + rhs.y);
		return  result;
	}
	// Subtracts the vectors and retern's as a new one.
	static Vector2<T> Sub (Vector2<T> const &lhs, Vector2<T> const &rhs) {
		Vector2 result (lhs.x - rhs.x, lhs.y - rhs.y);
		return  result;
	}
	// Get a new vector scaled from another.
	static Vector2<T> Mult (T const scalar, Vector2<T> const &v) {
		Vector2 result (v.x * scalar, v.y * scalar);
		return  result;
	}
	// Get a new vector scaled from another.
	static Vector2<T> Div (T const scalar, Vector2<T> const &v) {
		Vector2 result (v.x / scalar, v.y / scalar);
		return  result;
	}

	/*
	* ## Operator overloads
	*/

	// Adds the right-hand vector onto itself.
	Vector2<T>& operator += (const Vector2<T> &rhs) {
		Add(rhs);
		return *this;
	}
	// Adds the left and right-hand vector and returns a new one.
	Vector2<T>  operator + (const Vector2<T> &rhs) const {
		Vector2 result (x + rhs.x, y + rhs.y);
		return  result;
	}
	// Subtracts the right-hand vector from itself.
	Vector2<T>& operator -= (const Vector2<T> &rhs) {
		Sub(rhs);
		return *this;
	}
	// Returns a new vector that is the left subtracted by the right-hand vector.
	Vector2<T> operator - (const Vector2<T> &rhs) const {
		Vector2 result (x - rhs.x, y - rhs.y);
		return  result;
	}
	// Multiply this vector with the right-hand scalar.
	Vector2<T>& operator *= (T scalar) {
		Mult(scalar);
		return *this;
	}
	// Multiply the left-hand vector with the right-hand scalar, returns new vector.
	Vector2<T> operator * (T scalar) const {
		Vector2 result (x * scalar, y * scalar);
		return  result;
	}
	friend Vector2<T> operator *(T scalar, const Vector2<T> &v) {
		Vector2 result (v.x * scalar, v.y * scalar);
		return  result;
	}
	// Devide this vector with the right-hand scalar.
	Vector2<T>& operator /= (T scalar) {
		Div(scalar);
		return *this;
	}
	// Devide the left-hand vector with the right-hand scalar, returns new vector.
	Vector2<T> operator / (T scalar) const {
		Vector2 result (x / scalar, y / scalar);
		return  result;
	}
	friend Vector2<T> operator /(T scalar, const Vector2<T> &v) {
		Vector2 result (v.x / scalar, v.y / scalar);
		return  result;
	}
	// Gets the dot product of the two vectors.
	double operator *(const Vector2<T> &rhs) const {
		return Vector2::Dot(*this, rhs);
	}
	// Checks if the vectors are the same, ie: parallel and identical magnitude.
	bool operator==(const Vector2<T> &rhs) {
		return x == rhs.x && y == rhs.y;
	}
	// Opposite of ==
	bool operator!=(const Vector2<T> &rhs) {
		return !(*this == rhs);
	}

	// Casting
	operator Vector2<double>() const {
		return Vector2<double>(x, y);
	}
	operator Vector2<int>() const {
		return Vector2<int>(x, y);
	}
	operator Vector2<float>() const {
		return Vector2<float>(x, y);
	}

};

#endif // !__VECTOR2_H__
