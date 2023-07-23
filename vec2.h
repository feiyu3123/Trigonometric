#ifndef VEC2_H
#define VEC2_H

#include <cmath>
#include <string>
#include <sstream>
#include <stdio.h>



//================================================================================================const var================================================================================================
#ifndef M_E
#define M_E (2.7182818284590452354)
#endif

#ifndef M_LOG2E
#define M_LOG2E (1.4426950408889634074)
#endif

#ifndef M_LOG10E
#define M_LOG10E (0.43429448190325182765)
#endif

#ifndef M_LN2
#define M_LN2 (0.69314718055994530942)
#endif

#ifndef M_LN10
#define M_LN10 (2.30258509299404568402)
#endif

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

#ifndef M_PI_2
#define M_PI_2 (1.57079632679489661923)
#endif

#ifndef M_PI_4
#define M_PI_4 (0.78539816339744830962)
#endif

#ifndef M_1_PI
#define M_1_PI (0.31830988618379067154)
#endif

#ifndef M_2_PI
#define M_2_PI (0.63661977236758134308)
#endif

#ifndef M_2_SQRTPI
#define M_2_SQRTPI (1.12837916709551257390)
#endif

#ifndef M_SQRT2
#define M_SQRT2 (1.41421356237309504880)
#endif

#ifndef M_SQRT1_2
#define M_SQRT1_2 (0.70710678118654752440)
#endif

inline double deg2rad(double angle)
{
    double r = angle / (180.0 / M_PI);
    return r;
}

inline double rad2deg(double radian)
{
    double d = radian * (180.0 / M_PI);
    return d;
}

struct vec2
{
public:
    vec2();
    vec2(double e0, double e1);

    double length_squared() const;

    double length() const;

    vec2 dir() const;

    double operator[](int i) const;
    double& operator[](int i);

    vec2& operator+=(const vec2& rhs);
    vec2& operator-=(const vec2& rhs);
    vec2& operator*=(double s);
    vec2& operator/=(double s);
    std::string toString();
    double e[2];


};

inline vec2 operator+(const vec2& v1, const vec2& v2)
{
    vec2 v(v1[0] + v2[0],
            v1[1] + v2[1]);
    return v;
}

inline vec2 operator-(const vec2& v1, const vec2& v2)
{
    vec2 v(v1[0] - v2[0],
            v1[1] - v2[1]);
    return v;
}

inline vec2 operator*(const vec2& v1, double s)
{
    vec2 v(v1[0] * s, v1[1] * s);
    return v;
}

inline vec2 operator*(double s, const vec2& v1)
{
    return v1 * s;
}

inline vec2 operator/(const vec2& v1, double s)
{
    vec2 v(v1[0] / s, v1[1] / s);
    return v;
}


inline vec2 unit_vec2(const vec2& v1)
{
    vec2 v = v1 / v1.length();
    return v;
}

using point2=vec2;

/**
 * @brief The matrix2x2 2x2 矩阵
 */
struct matrix2x2
{
    double operator ()(int row,int col) const
    {
        return e[row][col];
    }

    double& operator ()(int row,int col)
    {
        return e[row][col];
    }

    double e[2][2];
};

inline double dot(const matrix2x2& m,const vec2& v,int r)
{
    double d=m(r,0)*v[0]+m(r,1)*v[1];
    return d;
}

inline vec2 operator*(const matrix2x2& lhs,const vec2& rhs)
{
    double x=dot(lhs,rhs,0);
    double y=dot(lhs,rhs,1);
    vec2 v(x,y);
    return v;
}


/**
 * @brief rotate_matrix 创建旋转矩阵
 * @param rotate_angle 旋转角
 * @return 旋转矩阵
 */
inline matrix2x2 rotate_matrix(double rotate_angle)
{//使用数学坐标系
    double rotate_rad=deg2rad(rotate_angle);
    matrix2x2 m;
    m(0,0)=cos(rotate_rad);
    m(0,1)=-sin(rotate_rad);
    //
    m(1,0)=sin(rotate_rad);
    m(1,1)=cos(rotate_rad);
    return m;
}

//================================================================================================Trigonometric functions================================================================================================


/**
 * @brief calc_triangle_area 使用海伦公式计算三角形面积
 * @param a_side_length a边长
 * @param b_side_length b边长
 * @param c_side_length c边长
 * @return 三角形面积
 */

inline double calc_triangle_area(double a_side_length, double b_side_length, double c_side_length)
{//参考海伦公式,求三角形面积
    double p = (a_side_length + b_side_length + c_side_length) / 2.0;
    double s = sqrt(p * (p - a_side_length) * (p - b_side_length) * (p - c_side_length));
    return s;
}

inline double calc_triangle_high(double s, double di)
{
    double h = 2.0 * s / di;
    return h;
}

inline double calc_triangle_inscribed_circle_r(const point2& A, const point2& B, const point2& C)
{//求内切圆半径
    double a_side_length = (B - C).length();
    double b_side_length = (A - C).length();
    double c_side_length = (A - B).length();
    double s = calc_triangle_area(a_side_length, b_side_length, c_side_length);
    double r = 2 * s / (a_side_length + b_side_length + c_side_length);
    return r;
}

inline double calc_triangle_circumscribed_circle_r(const point2& A, const point2& B, const point2& C)
{//求外接圆半径 r = abc/(4s)
    double a_side_length = (B - C).length();
    double b_side_length = (A - C).length();
    double c_side_length = (A - B).length();
    double s = calc_triangle_area(a_side_length, b_side_length, c_side_length);
    double  r = a_side_length * b_side_length * c_side_length / (4.0 * s);
    return r;
}

inline point2 calc_rotate_point(const point2& A, double r, double angle)
{//求旋转的点
    double rad = deg2rad(angle);
    double y = sin(rad);
    double x = cos(rad);
    point2 p(x, y);
    return p;
}

//------------------------------余弦函数相关------------------------------
inline double cosine_calc_angle(double c_side_length, double a_side_length, double b_side_length)
{//参考公式cos C=(a²+b²-c²)/2ab,求c边对应的角C
    double cosC = (a_side_length * a_side_length + b_side_length * b_side_length - c_side_length * c_side_length) / (2.0 * a_side_length * b_side_length);
    double rad = acos(cosC);
    double angle = rad2deg(rad);
    return angle;
}

inline double cosine_calc_side_length(double a_side_length, double b_side_length, double ab_angle)
{//参考公式c²=a²+b²-2ab cos C,求
    double rad = deg2rad(ab_angle);
    double cc = a_side_length * a_side_length + b_side_length * b_side_length - 2 * a_side_length * b_side_length * cos(rad);
    double c = sqrt(cc);
    return c;
}


//------------------------------正弦函数相关------------------------------
inline double sine_calc_2r(double a_side_length, double A_angle)
{//参考正弦
    double radA = deg2rad(A_angle);
    double _2r = a_side_length / sin(radA);
    return _2r;
}

inline double sine_calc_high(double c_side_length, double A_angle)
{//参考sin=对边边长/斜边边长,已知斜边和正弦夹角，求三角形高
    double radA = deg2rad(A_angle);
    double h = sin(radA) * c_side_length;
    return h;
}


//------------------------------矢量相关------------------------------


//------------------------------点积------------------------------


inline double dot(const vec2& v1, const vec2& v2)
{//点积a·b:将测量b投影到 a上的长度，乘以 a的长度。
    double d = v1.e[0] * v2.e[0]
            + v1.e[1] * v2.e[1];
    return d;
}

inline double dot_angle(const vec2& v1, const vec2& v2)
{//使用点乘公式，求两向量间的夹角C=acos( (a dot b)/(|a|*|b|) )
    double acosC = dot(v1, v2) / (v1.length() * v2.length());
    double radC = acos(acosC);
    double angle = rad2deg(radC);
    return angle;
}

//------------------------------叉积------------------------------

/**
 * @brief cross 叉积
 * @param v1 矢量1
 * @param v2 矢量2
 * @return
 */
inline double cross(const vec2& v1, const vec2& v2)
{//叉积
    double c = v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0];
    return c;
}

/**
 * @brief cross_is_clockwise 以矢量2为参考，判断矢量1是否为顺时针
 * @param v1 矢量1
 * @param v2 矢量2
 * @return
 */
inline bool cross_is_clockwise(const vec2& v1,const vec2 v2)
{//vec1矢量与vec2间是否为顺时针
    double c=cross(v1,v2);
    bool bRet=false;
    if(c<0)
        bRet=true;
    return bRet;
}

/**
 * @brief calc_vec_intersects 计算两矢量相交的交点
 * @param A 矢量1 起点
 * @param B 矢量1 终点
 * @param C 矢量2 起点
 * @param D 矢量2 终点
 * @return 两向量相交的交点
 */
inline point2 calc_vec_intersects(const point2& A,const point2&B,const point2&C,const point2&D)
{
    vec2 ab=B-A;//ab vec2
    vec2 cd=D-C;//cd vec2
    vec2 ca=A-C;
    double t=cross(cd,ca)/cross(ab,cd);
    point2 p=A+t*ab;
    return p;
}





//------------------------------示例------------------------------
void app_sample();











#endif

