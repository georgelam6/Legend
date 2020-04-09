#include "Vector2.h"


Vector2::Vector2() :
	x(0),
	y(0)
{}

Vector2::Vector2(int x, int y) :
	x(x),
	y(y)
{}

Vector2& Vector2::add(const Vector2& other)
{
	x += other.x;
	y += other.y;

	return *this;
}

Vector2& Vector2::multiply(const Vector2& other)
{
	x *= other.x;
	y *= other.y;

	return *this;
}

Vector2& Vector2::subtract(const Vector2& other)
{
	x -= other.x;
	y -= other.y;

	return *this;
}

Vector2& Vector2::divide(const Vector2& other)
{
	x /= other.x;
	y /= other.y;

	return *this;
}

std::ostream& operator<<(std::ostream& stream, const Vector2& vector)
{
	stream << "(" << vector.x << ", " << vector.y << ")";
	return stream;
}

Vector2& operator+(Vector2 left, const Vector2& right)
{
	return left.add(right);
}

Vector2& operator*(Vector2 left, const Vector2& right)
{
	return left.multiply(right);
}

Vector2& operator-(Vector2 left, const Vector2& right)
{
	return left.subtract(right);
}

Vector2& operator/(Vector2 left, const Vector2& right)
{
	return left.divide(right);
}


Vector2& Vector2::operator+=(const Vector2 other)
{
	return this->add(other);
}

Vector2& Vector2::operator*=(const Vector2 other)
{
	return this->multiply(other);
}

Vector2& Vector2::operator-=(const Vector2 other)
{
	return this->subtract(other);
}

Vector2& Vector2::operator/=(const Vector2 other)
{
	return this->divide(other);
}

float Vector2::DotProduct(const Vector2& other)
{
	return (other.x * this->x) + (other.y * this->y);
}