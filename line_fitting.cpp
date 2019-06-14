#include <bits/stdc++.h>
//#include "input_reader.hpp"
//#include "SegmentedLeastSquares.hpp"
using namespace std;
class input_reader{
    //! this class helps with taking input in different ways like user input etc 
    private:
        vector<pair<double,double> > points;
        int N;
    public:
        input_reader(int n){
            N=n;
            /*for(int i=0;i<n;i++){
                //adds points
            }*/
            addPoint(n);
        }
        void addPoint(double x,double y){
            //! this function helps in adding the given point to input
            // adds point(x,y) to pints
            points.push_back(make_pair(x,y));
            N++;
        }
        void addPoint(int n){
            //! adds n new user inputted points
            double x,y;
            cin>>n;
            for(int i=0;i<n;i++){
                //cout<<"enter point coordinates\n";
                cin>>x>>y;
                points.push_back(make_pair(x,y));
                N++;
            }
        }
        vector<pair<double,double> > getPoints(){
            //! gives points to the caller
            return points;
        }
        int getPointsSize(){
            //! gives no of points in data to caller
            return N;
        }
};
class SegmentedLeastSquares{
    private:
    //! A Vector of points each of which is a pair of doubles
    vector<pair<double,double> > points;
    //! Used to store segments
    vector<vector<pair<double,double> > >segments;
    //! It stores the errors of different segments
    vector<double>opt;
    //! Used to represent starting and ending index of a segment
    vector<int>seg_start;
    //! pair of a and b values
    vector<vector<pair<double,double> > >lines;
    double c;
    int n;
    ///
    /*!
    \param fileName file from which input is to be read
    */
    double OPT(int j){
        if(opt[j]!=-1)return opt[j];
        double small=INT_MAX;
        int temp;
        for(int i=1;i<=j;i++){
            double val = c+leastSquareError(i,j)+OPT(i-1);
            if(val<small){
                small=val;
                temp=i;
            }
        }
        seg_start.push_back(temp);
        opt[j]=small;
        return opt[j];

    }
    ///It gives least square error of a segment
    /*!
    \param start starting index of a segment
    \param end ending index of a segment
    */
    double leastSquareError(int start,int end){
        double a,b;
        int N=end-start+1;
        double sigx=0,sigy=0,sigxy=0,sig2x=0;
        for(int i=start;i<=end;i++){
            sigx +=points[i].first;
            sigy +=points[i].second;
            sigxy += points[i].first*points[i].second;
            sig2x +=  points[i].first*points[i].first;
        }
        a = (N*sigxy-sigx*sigy)/(N*sig2x-sigx*sigx);
        b = (sigy-a*sigx)/N;
        double sum=0;
        for(int i=start;i<=end;i++){
            double temp = points[i].second-a*points[i].first-b;
            sum+=temp*temp;
        }
        lines[start][end]=make_pair(a,b);
        return sum;
    }
    ///Generates segments
    /*!
    */
    void segmentsGenerator(){
        int end=n;
        int start=seg_start[end];
        while(end>=1){
            vector<pair<double,double> >temp;
            cout<<lines[start][end].first<<" "<<lines[start][end].second<<endl;
            for(int i=start;i<=end;i++){
                temp.push_back(points[i]);
            }
            segments.push_back(temp);
            end=start-1;
            start = seg_start[end];
        }
    }
    public:
    ///segmented least squares main implementation
    /*!
    \param Points vector of pair of doubles
    \param C cost 
    */
    SegmentedLeastSquares(vector<pair<double,double> >Points,double C){

        c=C;
        sort(Points.begin(),Points.end());
        points.push_back(make_pair(-1,-1));
        points.insert(points.end(),Points.begin(),Points.end());

        n = points.size()-1;
        
        vector<double>temp(n+1,-1);
        opt=temp;
        opt[0]=0;
        seg_start.push_back(-1);
        vector<vector<pair<double,double> > >slopes(n+1,vector<pair<double,double>>(n+1,make_pair(-1,-1)));
        lines=slopes;
        OPT(n);
        segmentsGenerator();
    }
    void printer(){
        //cout<<"cool "<<segments.size(); 
        for(auto seg: segments){
            cout<<"$"<<endl;
            for(auto pt:seg){
                cout<<pt.first<<" "<<pt.second<<endl;
            }
        }
        cout<<"$"<<endl;
    }
    vector<vector<pair<double,double> > > getSegments(){
        return segments;
    }

};

int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif
    input_reader inputReader(10);
    vector<pair<double,double> > points = inputReader.getPoints();
    //cout<<points.size()<<endl;
    for(int i=1; i<101; i++){
        cout << "$" << endl;
        SegmentedLeastSquares obj(points, i);
        obj.printer();
        cout<<endl;
    }
    //obj.printer();
}