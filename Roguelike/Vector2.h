#pragma once

#include <iostream>


struct Vector2
{
	int x, y;


	Vector2();
	Vector2(int x, int y);

	Vector2& add(const Vector2& other);
	Vector2& multiply(const Vector2& other);
	Vector2& subtract(const Vector2& other);
	Vector2& divide(const Vector2& other);

	friend Vector2& operator+(const Vector2 left, const Vector2& right);
	friend Vector2& operator*(const Vector2 left, const Vector2& right);
	friend Vector2& operator-(const Vector2 left, const Vector2& right);
	friend Vector2& operator/(const Vector2 left, const Vector2& right);

	Vector2& operator+=(const Vector2 other);
	Vector2& operator*=(const Vector2 other);
	Vector2& operator-=(const Vector2 other);
	Vector2& operator/=(const Vector2 other);

	friend std::ostream& operator<<(std::ostream& stream, const Vector2& vector);

	float DotProduct(const Vector2& other);
};