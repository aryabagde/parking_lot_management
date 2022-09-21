#include<iostream>
#include<vector>
using namespace std;

struct time{            // new datatype
    int hour;
    int min;
    int sec;
    char c1;           // colons in time
    char c2;
};

struct date{
  int day;
  int month;
  int year;
  char s1;             //slashes in date
  char s2;
};

class vehicle{
	string pltno;
	string pay;
    int type;                 // car, bike, handicap
    date dt;
    time arrive;
    time departure;

public:
    void addVehicle();
    void deleteVehicle();
    void printvehicle(vehicle v);
    void show();
};

vector<vehicle> veh(100);                                                                     // vector declaration
int static totalvehicle=0,totalcar=0,totalbike=0,totalhandicap=0,totalamt=0,i=0;             // static declaration

//fstream file;

void vehicle::addVehicle(){                                                   //member function 1

	vehicle *v = new vehicle;                                                 //pointer for new object
    cout<<"Enter vehicle type(1 for Car/2 for Bike/3 for Handicap) : ";
    cin>>v->type;
    cout<<"Enter vehicle number: ";
    cin>>v->pltno;
    cout<<"Enter arrival time in hh/mm/ss: ";
    cin>>v->arrive.hour>>v->arrive.c1>>v->arrive.min>>v->arrive.c2>>v->arrive.sec;   // arrive ad departure are time variables
    cout<<"Enter date in dd/mm/yyyy: ";
    cin>>v->dt.day>>v->dt.s1>>v->dt.month>>v->dt.s2>>v->dt.year;        
	
	veh.at(i).pltno=v->pltno;                                                  // .at(g)  returns a reference to the element at position ‘g’ in the vector             
    veh.at(i).type=v->type;
    veh.at(i).arrive.hour=v->arrive.hour;
    veh.at(i).arrive.min=v->arrive.min;
    veh.at(i).arrive.sec=v->arrive.sec;
    veh.at(i).dt.day=v->dt.day;
    veh.at(i).dt.month=v->dt.month;
    veh.at(i).dt.year=v->dt.year;		
    
    i++;                                                                       // no need to use .push() since we are incrementing the index value
    totalvehicle++;
    
    if(v->type == 1){                                                         // count of vehicles category wise
        totalcar++;
    } else if(v->type == 2){
        totalbike++;
    } else{
    	totalhandicap++;
	}

    cout<<"\nVehicle added successfully"<<endl;
};

int timeDifference(time t1,time t2){

    int s1, s2, total;
    time t3;                                                          //dummy object 
	s1 = t1.hour*60*60 + t1.min*60 + t1.sec;                        // cconverting in seconds
    s2 = t2.hour*60*60 + t2.min*60 + t2.sec;

    total = s2-s1;

    t3.min = total/60;                                              //converting back to hours, min and sec
    t3.hour = t3.min/60;
    t3.min = t3.min%60;
    t3.sec = total%60;

   return t3.hour;                                                       // rerturning object rather than difference 
}

void vehicle:: deleteVehicle(){
      string pno, pay_mode;
      int typ,num;
      time depart;
      int timeDiff;
      int charge=0;

      cout<<"Enter vehicle type(1 for Car/2 for Bike/3 for Handicap):";
      cin>>typ;
      cout<<"Enter vehicle number: ";
      cin>>pno;
      cout<<"Enter departure time in hh/mm/ss: ";
      cin>>depart.hour>>depart.c1>>depart.min>>depart.c2>>depart.sec;                            // again depart is time varaiable



      for(int j=0;j<=i;j++){
            if((veh.at(j).pltno==pno)&&(veh.at(j).type==typ)){                                     // check if the vehicle exist
            	
                veh.at(j).departure.hour=depart.hour;                                              // assigning values after checking
                veh.at(j).departure.min=depart.min;
                veh.at(j).departure.sec=depart.sec;

                timeDiff = timeDifference(veh.at(j).arrive,depart);                                // time difference

                if(veh.at(j).type == 1){                                                           // Car
              	
                  	totalcar--;
                  
                	if(timeDiff <= 1){
                		charge = 80;                                                                 // charge 80 for 1st hour
                	} else if((timeDiff == 2) || (timeDiff == 3)){                                   // charge 150 for 2nd and 3rd hour
                		charge = 100;                  	
					}
                	else{
                    	charge = 150;                                                                // charge 150 for above 3 hours
                	}

                }
                else if(veh.at(j).type == 2){                                                      // Bike
              	
                	totalbike--;
					if((timeDiff == 1) || (timeDiff < 1)){
                		charge = 80;
                	} else if((timeDiff == 2) || (timeDiff == 3)){
                		charge = 100;                  	
					}
                	else{
                    	charge = 150;
                	}
                

                }
                else{
              	
            		totalhandicap--;                                                                 // Handicap vehicles
            		if((timeDiff == 1) || (timeDiff < 1)){
                		charge = 80;
                	} else if((timeDiff == 2) || (timeDiff == 3)){
                		charge = 100;                  	
					}
                	else{
                    	charge = 150;
                	}
			    }
			    
			    pay_mode = veh.at(j).pay;                                                             // payment mode
			  	cout<<"\nMode of Payment(1 for CASH/ 2 for CREDIT CARD/ 3 for DEBIT CARD): ";
			  	cin>>num;
			  	if(num == 1){
			  		pay_mode = "Cash";
				  }
				else if(num == 2){
					pay_mode = "Credit Card";
				}
				else if(num == 3){
					pay_mode = "Debit Card";
				}
            	cout<<"\nVehicle: "<<veh.at(j).pltno<<" is leaving parking lot after paying Rs. "<<charge<<" using "<<pay_mode<<"."<<endl;
            	veh.erase(veh.begin() + j);                                                                     // erasing a specific vector element
				i--;
                totalvehicle--;
                totalamt = totalamt+charge;                                                                     // increment in total amount
                break;

          }

          if(j==i){
              cout<<"\nWrong Entry, Try Again "<<endl;
              deleteVehicle();
          }
      }
}

void vehicle::printvehicle(vehicle v){
    cout<<v.type<<"\t\t\t"<<v.pltno<<"\t\t\t"<<v.dt.day<<"/"<<v.dt.month<<"/"<<v.dt.year<<"\t\t\t\t"<< v.arrive.hour<<":"<<v.arrive.min<<":"<<v.arrive.sec<<endl;
}

void vehicle::show(){
    cout<<"Vehicle Type\t\tVehicle Number\t\t\tDate\t\t\tArrival Time"<<endl;                // table view of all the vehicles
    for(int j=0;j<i;j++)                                                                     // looping through vector
    {
        printvehicle(veh[j]);
    }
}

void totalveh(){
      cout<<"Total number of vehicle parked: "<<totalvehicle<<endl;
      cout<<"Total number of car parked: "<<totalcar<<endl;
      cout<<"Total number of bike parked: "<<totalbike<<endl;
      cout<<"Total number of handicap vehicles parked: "<<totalhandicap<<endl;
      cout<<"Number of parking lots remaining: "<< 5-totalvehicle <<endl;
}

void totalamount(){
      cout<<"Total Collection till now : "<<totalamt<<endl;
}

int main(){
    int choice;
    char ans;
    system ("cls") ;

do{
    system ("cls") ;
    cout<<"--------------------------------------------------------------------"<<endl;
    cout<<"                 PARKING LOT REGISTRATION SYSTEM                    "<<endl;
    cout<<"1. Arrival of a vehicle"<<endl;
    cout<<"2. Departure of vehicle"<<endl;
    cout<<"3. Total number of vehicles parked"<<endl;
    cout<<"4. Total Amount collected"<<endl;
    cout<<"5. Display"<<endl;
    cout<<"6. Exit"<<endl;
    cout<<"--------------------------------------------------------------------"<<endl;
    cout<<"Enter your Choice: ";
    cin>>choice;

	switch(choice){
		
            case 1: system ( "cls" ) ;
                    if(totalvehicle < 5){                                               // The total limit for parking lot is considered 5(NOT CATEGORY WISE)
                    	cout<<"Add : "<<endl;
                    	veh.at(i).addVehicle();
					}
                    else{
                    	cout<<"Parking lot is full"<<endl;                             // no more addition after 5 vehicles
					}
                    
                    break;

            case 2: system ( "cls" ) ;
                    cout<<"Departure : "<<endl;
                    veh.at(i).deleteVehicle();
                    break;

            case 3: system ( "cls" ) ;
                    totalveh();
                    break;

            case 4: system ( "cls" ) ;
                    totalamount();
                    break;

            case 5: system ( "cls" ) ;
                    veh.at(i).show();
                    break;
                    
            case 6: exit(0);
        }

        cout<<"\nDo you want to continue, press y/n : "<<endl;
        cin>>ans;
        if(ans=='n'){
            break;
        }else{
            continue;
        }

	}while(1);

  return 0;
}

