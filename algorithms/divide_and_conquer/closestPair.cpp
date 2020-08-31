#include <iostream>
#include <vector>
#include <stdio.h>
#include <math.h>

using namespace std;

class Point{
public:
    double x;
    double y;

    Point (double input_x, double input_y): x(input_x), y(input_y) {}
    Point(){}
};

bool sort_by_x (const Point& a,const Point& b) {
    return a.x < b.x;
    }

bool sort_by_y(const Point& a, const Point& b){
    if(a.y == b.y) return a.x < b.x;
    return a.y < b.y;
    }

double getDistance(const Point& a, const Point& b) {
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y)); 
}

double mergeAndGetDistance(vector<Point>& points, int left, int mid, int right, double d);

double getMinDistance(vector<Point>& points, int left, int right){
    if(left == right) return INT64_MAX;
    if(left + 1 == right) return getDistance(points[left], points[right]);

    int mid = left + ((right - left)>>1);
    double d_left = getMinDistance(points, left, mid);
    double d_right = getMinDistance(points, mid+1, right);

    double d = min(d_left, d_right);

    return mergeAndGetDistance(points, left, mid, right, d);
}


double mergeAndGetDistance(vector<Point>& points, int left, int mid, int right, double d){

    vector<Point> dFromMid;

    for(int i =left;i<=right;++i)
    {
        if(fabs(points[i].x - points[mid].x) < d)
        {
            dFromMid.push_back(points[i]);
        }
    }

    sort(dFromMid.begin(), dFromMid.end(), sort_by_y);

    for (int i = 0; i < dFromMid.size(); ++i)
    {
        /* code */
        for(int j = i+1;j < dFromMid.size();++j)
        {
            if(points[j].y - points[i].y> d) break;
            else
            {
                double cur_distance = getDistance(points[i], points[j]);
                if(cur_distance < d)
                {
                    d = cur_distance;
                }
            }
            
        }
    }
    return d;
}

int main(){
    int n;
    cout << "Input the amount of points:"<<endl;
    cin >> n;

    vector<Point> points(n);

    for (int i = 0; i < n; i++)
    {
        cout<< "Input the x of the " << i+1 << "th point:"<<endl;
        cin >> points[i].x;
        cout<< "Input the y of the " << i+1 << "th point:"<<endl;
        cin >> points[i].y;
    }

    sort(points.begin(), points.end(), sort_by_x);

    double d = getMinDistance(points, 0, points.size()-1);

    cout << "the closest distance is:" << d << endl;

    return 0; 

}
