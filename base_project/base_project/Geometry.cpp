#include"Geometry.h"
#include<DxLib.h>
#include<cmath>

constexpr float pi = 3.14159265358979f;
constexpr float deg_to_rad = pi / 180.0f;
constexpr float rad_to_deg = 180.0f / pi;
constexpr float two_pi = pi * 2.0f;
constexpr float inv_two_pi = 1.0f / two_pi;
constexpr float helf_pi = pi / 2.0f;
constexpr float inv_half_pi = 1.0f / helf_pi;
constexpr float epsilon = 1.0e-6f;
constexpr float head_size = 10.0f; // 矢印先端の大きさ
constexpr float line_thickness = 3.0f; // 線の太さ
constexpr float dash_length = 5.0f; // 点線の長さ

void
Rect::Draw(unsigned int color,bool fill) {
	DxLib::DrawBoxAA(Left() , Top() , Right() , Bottom(), color, fill,line_thickness);
}

void
Rect::Draw(Vector2& offset) {
	DxLib::DrawBoxAA((Left() + offset.x) , (Top() + offset.y), (Right() + offset.x), (Bottom() + offset.y), 0xffffffff, false,line_thickness);
}
std::array<Position2, 4> 
Rect::GetPositions()const {
	std::array<Position2, 4> verts;
	verts[0] = Vector2(Left(), Top());
	verts[1] = Vector2(Right(), Top());
	verts[2] = Vector2(Left(), Bottom());
	verts[3] = Vector2(Right(), Bottom());
	return verts;
}
void
Vector2::operator*=(float scale) {
	x *= scale;
	y *= scale;
}

Vector2
Vector2::operator*(float scale) const{
	return { x * scale, y * scale };
}

Vector2 operator+(const Vector2& va, const Vector2 vb) {
	Vector2 ret;
	ret.x = va.x + vb.x;
	ret.y = va.y + vb.y;
	return ret;
}

Vector2 operator-(const Vector2& va, const Vector2 vb) {
	return { va.x - vb.x, va.y - vb.y };
}

float
Vector2::Length()const {
	return std::hypot(x, y);
}


void
Vector2::Normalize() {
	float mag = Length();
	if (mag < epsilon){
		x = 0.0f;
		y = 0.0f;
		return;
	}
	x /= mag;
	y /= mag;
}


Vector2
Vector2::Normalized()const {
	float mag = Length();
	if (mag < epsilon) {
		return {0.0f,0.0f};
	}
	return {x / mag, y / mag};
}


///内積を返す
float
Dot(const Vector2& va, const Vector2& vb) {
	return va.x*vb.x + va.y*vb.y;
}

///外積を返す
float
Cross(const Vector2& va, const Vector2& vb) {
	return va.x*vb.y - vb.x*va.y;
}

///内積演算子
float
operator*(const Vector2& va, const Vector2& vb) {
	return Dot(va, vb);
}

///外積演算子
float
operator%(const Vector2& va, const Vector2& vb) {
	return Cross(va, vb);
}


void
Vector2::operator+=(const Vector2& v) {
	x += v.x;
	y += v.y;
}
void
Vector2::operator-=(const Vector2& v) {
	x -= v.x;
	y -= v.y;
}


///２つの行列の乗算を返す
///@param lmat 左辺値(行列)
///@param rmat 右辺値(行列)
///@attention 乗算の順序に注意してください
Matrix
MultipleMat(const Matrix& lmat, const Matrix& rmat) {
	Matrix ret = {};

	for (int k = 0; k <= 2; ++k) {
		for (int j = 0; j <= 2; ++j) {
			for (int i = 0; i <= 2; ++i) {
				ret.m[k][j] += lmat.m[k][i] * rmat.m[i][j];
			}
		}
	}

	return ret;

}

Matrix operator*(const Matrix& lmat, const Matrix& rmat) {
	return MultipleMat(lmat, rmat);
}

///ベクトルに対して行列乗算を適用し、結果のベクトルを返す
///@param mat 行列
///@param vec ベクトル
Vector2
MultipleVec(const Matrix& mat, const Vector2& vec) {
	Vector2 ret = {};
	ret.x = mat.m[0][0] * vec.x + mat.m[0][1] * vec.y + mat.m[0][2];
	ret.y = mat.m[1][0] * vec.x + mat.m[1][1] * vec.y + mat.m[1][2];
	return ret;
}
Vector2 operator*(const Matrix& mat, const Vector2& vec) {
	return MultipleVec(mat, vec);
}

float DegToRad(float deg)
{
	return deg * deg_to_rad;
}

float RadToDeg(float rad)
{
	return rad * rad_to_deg;
}

///単位行列を返す
Matrix IdentityMat() {
	Matrix ret = {};
	ret.m[0][0] = ret.m[1][1] = ret.m[2][2] = 1;
	return ret;
}

///平行移動行列を返す
///@param x X方向平行移動量
///@param y Y方向平行移動量
Matrix TranslateMat(float x, float y) {
	Matrix ret = {};
	ret = IdentityMat();
	ret.m[0][2] = x;
	ret.m[1][2] = y;
	return ret;
}

///回転行列を返す
///@param angle 回転角度
Matrix RotateMat(float angle) {
	Matrix ret = {};
	ret = IdentityMat();
	ret.m[0][0] = cos(angle);
	ret.m[0][1] = -sin(angle);
	ret.m[1][0] = sin(angle);
	ret.m[1][1] = cos(angle);
	return ret;
}

void Circle::Draw(unsigned int color, bool fill)
{
	DrawCircleAA(pos.x, pos.y, radius, 32, color, fill,line_thickness);
}

void Capsule::Draw(unsigned int color, bool fill)
{
	DrawCircleAA(posA.x, posA.y, radius, 32, color, fill, line_thickness);
	DrawCircleAA(posB.x, posB.y, radius, 32, color, fill, line_thickness);
	Vector2 vec = posB - posA;
	vec.Normalize();
	Vector2 perp(-vec.y, vec.x);
	Vector2 p1 = posA + perp * radius;
	Vector2 p2 = posA - perp * radius;
	Vector2 p3 = posB + perp * radius;
	Vector2 p4 = posB - perp * radius;
	DxLib::DrawLineAA(p1.x, p1.y, p3.x, p3.y, color, line_thickness);
	DxLib::DrawLineAA(p2.x, p2.y, p4.x, p4.y, color, line_thickness);
}

void Arrow::Draw(unsigned int color)
{
	// 方向ベクトルの計算
	auto vec = end - start;
    
    if (vec.Length()< epsilon) return;
    
	float angle = std::atan2(vec.y, vec.x);
    
	// 単位方向ベクトル
	auto nvec = vec.Normalized();

	// 先端羽左右の計算
	Position2 left, right;
	left = end - nvec * headSize + Position2(-nvec.y, nvec.x) * (headSize / 2);
	right = end - nvec * headSize + Position2(nvec.y, -nvec.x) * (headSize / 2);
	    
    // 棒を描画
    DrawLineAA(start.x,start.y,
			end.x,end.y, color, lineThickness);
    
    // 矢印先端を描画
    if (headType == ArrowHeadType::V) {
        // ∧型：線のみ
        DrawLineAA(end.x,end.y,left.x,left.y, color, lineThickness);
		DrawLineAA(end.x,end.y,right.x,right.y, color, lineThickness);
    } else {
        // ▲型：塗りつぶし三角形
		DrawTriangleAA(end.x, end.y, left.x, left.y, right.x, right.y,color, true, lineThickness);
    }
}

void DashedArrow::Draw(unsigned int color)
{
		// 方向ベクトルの計算
	auto vec = end - start;
    
    if (vec.Length()< epsilon) return;
    
	float angle = std::atan2(vec.y, vec.x);
    
	// 単位方向ベクトル
	auto nvec = vec.Normalized();

	// 先端羽左右の計算
	Position2 left, right;
	left = end - nvec * headSize + Position2(-nvec.y, nvec.x) * (headSize / 2);
	right = end - nvec * headSize + Position2(nvec.y, -nvec.x) * (headSize / 2);
	
	Position2 segStart = start;
	Position2 segEnd = start+nvec*dash_length;
	// 点線- - - -棒を描画
	while(1){	
		DrawLineAA(segStart.x,segStart.y,
			segEnd.x,segEnd.y, color, lineThickness);
		
		segStart = segEnd + nvec * dash_length;
		segEnd = segStart + nvec * dash_length;
		if((segEnd-start).Length()>vec.Length()){
			break;
		}
	}
    
    
    
    // 矢印先端を描画
    if (headType == ArrowHeadType::V) {
        // ∧型：線のみ
        DrawLineAA(end.x,end.y,left.x,left.y, color, lineThickness);
		DrawLineAA(end.x,end.y,right.x,right.y, color, lineThickness);
    } else {
        // ▲型：塗りつぶし三角形
		DrawTriangleAA(end.x, end.y, left.x, left.y, right.x, right.y,color, true, lineThickness);
    }
}
