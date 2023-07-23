#include "vec2.h"

vec2::vec2()
{

}

vec2::vec2(double e0, double e1)
{
    e[0] = e0;
    e[1] = e1;
}

double vec2::length_squared() const
{
    double s = e[0] * e[0] + e[1] * e[1];
    return s;
}

double vec2::length() const
{
    double s = length_squared();
    double l = sqrt(s);
    return l;
}

vec2 vec2::dir()const
{
    vec2 v=(*this);
    v/=length();
    return v;
}

double vec2::operator[](int i) const
{
    return e[i];
}

double& vec2::operator[](int i)
{
    return e[i];
}

vec2& vec2::operator+=(const vec2& rhs)
{
    e[0] += rhs.e[0];
    e[1] += rhs.e[1];
    return *this;
}

vec2& vec2::operator-=(const vec2& rhs)
{
    e[0] -= rhs.e[0];
    e[1] -= rhs.e[1];
    return *this;
}

vec2& vec2::operator*=(double s)
{
    e[0] *=s;
    e[1] *=s;
    return *this;
}

vec2& vec2::operator/=(double s)
{
    e[0] /= s;
    e[1] /= s;
    return *this;
}

std::string vec2::toString()
{
    std::stringstream ss;
    ss << "(" << e[0];
    ss << "," << e[1];
    ss << ")";

    std::string s = ss.str();
    return s;
}


void app_sample()
{

    //------------------------------矢量点积相关------------------------------

    {//已知任意两矢量,求两矢量间的夹角
        vec2 a(2, 2);
        vec2 b(1, 0);
        double C = dot_angle(a, b);

        char buffer[1024] = {};
        sprintf(buffer, "已知任意两矢量，求两矢量间的夹角。\n                例：a %s,b %s 求出两矢量夹角:%f°\n\n"
                , a.toString().c_str()
                , b.toString().c_str()
                , C);
        printf(buffer);
    }

    {//点积的投影计算
        vec2 a(2, 2);
        vec2 b(100, 0);
        b = unit_vec2(b);//归一化，去掉长度
        double d = dot(a, b);//a在b上的投影,这里保留了a的模长

        char buffer[1024] = {};
        sprintf(buffer, "求投影的长度。\n                例：a %s,b %s 求a在b上投影的长度:%f\n\n"
                , a.toString().c_str()
                , b.toString().c_str()
                , d);
        printf(buffer);
    }



    //------------------------------余弦函数相关------------------------------

    {//已知三角形两条边的长和两条边间的夹角，求夹角的对边边长
        double a_side_length = 1;
        double b_side_length = 1;
        double ab_angle = 90;
        double c_side_length = cosine_calc_side_length(a_side_length, b_side_length, ab_angle);

        char buffer[1024] = {};
        sprintf(buffer, "已知两条边长和这两条边的夹角，求这个角的对边边长。\n                例：a:%f,b:%f,a与b的夹角:%f,求出对边:%f\n\n"
                , a_side_length
                , b_side_length
                , ab_angle
                , c_side_length);
        printf(buffer);
    }

    {
        //1、已知三边，找其中一个边为底，求高
        //2、已知三边，求其中一条边的对角

        double a = 1;
        double b = sqrt(3);
        double c = sqrt(a * a + b * b);
        double s = calc_triangle_area(a, b, c);//计算面积
        double h = calc_triangle_high(s, c);//c为底,换算高
        double C = cosine_calc_angle(c, a, b);

        char buffer[1024] = {};
        sprintf(buffer, "已知三条边的边长，以任意一条边为底，计算与这条边相垂直的高。\n                例：a:%f,b:%f,c:%f,求出垂直于c为底三角形的高:%f，求出c边的对角:%f°\n\n"
                , a
                , b
                , c
                , h
                , C);
        printf(buffer);


    }

    //------------------------------------------------------------
    {//正三角形求外接圆半径
        double r0 = 1;
        point2 A(0, 0);
        point2 B = calc_rotate_point(A, r0, 60);
        point2 C(r0, 0);

        //
        double a_side_length = (B - C).length();
        double b_side_length = (A - C).length();
        double c_side_length = (A - B).length();
        double angle = cosine_calc_angle(c_side_length, a_side_length, b_side_length);
        //

        double r = calc_triangle_circumscribed_circle_r(A, B, C);//外接圆半径
        //测试
        double _2r = 2 * r;
        double h = cosine_calc_side_length(_2r, r0, 30);
        double di = sqrt(_2r * _2r - h * h);
        //这里可以看到di==r0
        bool debug = true;
    }

    {//计算从点A过点B的延长线
        point2 A(0,0);
        point2 B(100,100);
        vec2 v1=(B-A);
        vec2 dir=v1/v1.length();
        double s=10;
        point2 C=B+dir*s;

        char buffer[1024] = {};
        sprintf(buffer, "计算从点A过点B的延长线。\n                例：从点A:%s过点B:%s延长:%f。求出C:%s\n\n"
                , A.toString().c_str()
                , B.toString().c_str()
                , s
                , C.toString().c_str());

    }

    {//判断按cd作为参考，ab与cd的方向是顺时针还是逆时针
        vec2 ab(0,1);
        vec2 cd(1,0);
        bool isClockwise=cross_is_clockwise(ab,cd);


        char buffer[1024] = {};
        sprintf(buffer, "判断按cd作为参考，ab与cd的方向是顺时针还是逆时针。\n                例：ab:%s，cd:%s。求出是否为顺时针：%s\n\n"
                , ab.toString().c_str()
                , cd.toString().c_str()
                ,isClockwise?"true":"false");

    }


    {//任意两矢量相交的点坐标
        vec2 A(1.5,0.5);
        vec2 B(2,1);
        vec2 C(0.5,0);
        vec2 D(1,0);
        point2 p=calc_vec_intersects(A,B,C,D);

        bool debug = true;
    }

    {//使用旋转矩阵处理向量旋转
        matrix2x2 m=rotate_matrix(90);
        vec2 a(1,1);
        vec2 a1=m*a;

        double angle=dot_angle(a1,a);


        bool debug = true;

    }


    {//给任意一个点和任意不相交向量，计算垂线交点
        //任意一点
        point2 A(10,10);
        //任意不相交向量中的两点
        point2 B(1,0);
        point2 C(2,1);
        //
        vec2 bc=C-B;
        vec2 ba=A-B;
        double shadow= dot(ba,bc.dir());


        bool debug = true;
    }
}


