#include "MathUtilityForText.h"

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rot, const Vector3& translate) { return Matrix4x4(); }

Vector3& operator+=(Vector3& lhs, const Vector3& rhv) {
	// TODO: return ステートメントをここに挿入します
	lhs.x += rhv.x;
	lhs.y += rhv.y;
	lhs.z += rhv.x;
	return lhs;
}