#include<iostream>
using namespace std;
class OBST
{
    public:
            int n;
            int key[10],p[10],q[10],w[10][10],r[10][10],c[10][10];

        void accept()
        {
            cout<<"enter number of keys: ";
            cin>>n;
            for(int i=1;i<=n;i++)
            {
                cout<<"enter "<<i<<"key: ";
                cin>>key[i];
            }
            cout<<"enter "<<n<<" succuessful proba: ";
            for(int i=1;i<=n;i++)
            {
                cin>>p[i];
            }
            cout<<"enter "<<n+1<<"unsucc prob: ";
            for(int i=0;i<=n;i++)
            {
                cin>>q[i];
            }
        }

         void calculate_w()
        {
            for(int i=0;i<=n;i++)
            {

                for(int j=i;j<=n;j++)
                {
                    if(i==j)
                    {
                        c[i][j] = 0;
                        r[i][j] = 0;
                        w[i][j]=q[i];
                        //cout<<i<<j<<":"<<w[i][j]<<"\t";
                    }
                    else
                    {
                        w[i][j]=w[i][j-1]+p[j]+q[j];
                        //cout<<i<<j<<":"<<w[i][j]<<"\t";
                    }
                }
            }
        }


        void calculate_c()
        {
            for(int m=1;m<=n;m++)
            {
                for(int i=0;i<=n-m;i++)
                {
                   int j=i+m;
                   int min=9999;
                   for(int k=i+1;k<=j;k++)
                   {
                    int cost=c[i][k-1]+c[k][j];
                    if(cost<min)
                    {
                        min=cost;
                        r[i][j]=k;
                    }
                   }
                   c[i][j]=min+w[i][j];
                   //cout<<i<<j<<":"<<c[i][j]<<"\t";
                   //cout<<i<<j<<":"<<r[i][j]<<"\t";
                }
            }
        }

        void display()
        {
            cout<<"weight matrix: \n";
            for(int i=0;i<=n;i++)
            {
                for(int j=i;j<=n;j++)
                {
                    cout<<"w"<<i<<j<<":"<<w[i][j]<<"\t";
                }
                cout<<endl;
            }
            cout<<"cost matrix: \n";
            for(int i=0;i<=n;i++)
            {
                for(int j=i;j<=n;j++)
                {
                    cout<<"c"<<i<<j<<":"<<c[i][j]<<"\t";
                }
                cout<<endl;
            }
            cout<<"root matrix: \n";
            for(int i=0;i<=n;i++)
            {
                for(int j=i;j<=n;j++)
                {
                    cout<<"r"<<i<<j<<":"<<r[i][j]<<"\t";
                }
                cout<<endl;
            }
        }
        
};
int main()
{
    OBST o;
    o.accept();
    o.calculate_w();
    o.calculate_c();
    o.display();
    return 0;
}