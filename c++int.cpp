#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;
class TaxPayer
{
		char *Name, *filer;
		double property_Value;
	public:
		~TaxPayer()
		{
			delete []Name;
			delete []filer;
		}
		TaxPayer(char *Name, double property_Value, char *filer)
		{
			int length = strlen(Name);
	
			this->Name = new char[length+1];
			strcpy(this->Name, Name);
			
			length = strlen(filer);
			this->filer = new char[length+1];
			strcpy(this->filer, filer);
			
			
			this->property_Value = property_Value;
		}
		double GetPropertyValue()
		{	return property_Value;	}
		double GetAdvanceIncomeTax()
		{
			double incomeTax=0.0;
			if(strcmp(filer, "Filer")==0)
				incomeTax = property_Value * 0.02;
			else
				incomeTax = property_Value * 0.04;
				
			return incomeTax;
		}
		virtual void TaxPayerInfo()
		{
			cout<<"Tax Payer Name: "<<Name<<endl;
			cout<<"Property Value: "<<property_Value<<endl;
		}
		virtual void Calculate_Total_Tax()=0;
};
class Seller:public TaxPayer
{
		double CapitalGainTax, Property_Purchase_Price, profit, TotalTax;
		int soldyear;
	public:
		Seller(char *Name, double property_Value, double Property_Purchase_Price, char *filer, int soldyear):TaxPayer(Name, property_Value, filer)
		{
			this->Property_Purchase_Price = Property_Purchase_Price;
			this->soldyear = soldyear;
		}
		double Calculate_CGT()
		{
			if(soldyear <=3 && soldyear>0)
			{
				profit=GetPropertyValue() - Property_Purchase_Price;
				switch(soldyear)
				{
					case 1:
						{
							CapitalGainTax=profit * 0.10;
							break;
						}
					case 2:
						{
							CapitalGainTax=profit * 0.075;
							break;
						}
					default:
						{
							CapitalGainTax=profit * 0.05;
							break;
						}
				}
				return CapitalGainTax;
			}
		}
		virtual void Calculate_Total_Tax()
		{
			TotalTax=GetAdvanceIncomeTax() + Calculate_CGT();
			cout<<"Seller Tax"<<endl<<"----------"<<endl<<endl;
			TaxPayerInfo();
			cout<<"Sold Year: "<<soldyear<<endl;
			cout<<"Income Tax: "<<GetAdvanceIncomeTax()<<endl;
			cout<<"Capital Gain Tax: "<<CapitalGainTax<<endl;
			cout<<"Total Tax of Seller: "<<TotalTax<<endl;
		}
};
class Purchaser:public TaxPayer
{
		double CapitalValueTax, Stamp_duty, TotalTax;
	public:
		Purchaser(char *Name, double property_Value, char *filer):TaxPayer(Name, property_Value, filer)
		{}
		virtual void Calculate_Total_Tax()
		{
			double value=GetPropertyValue();
			
			CapitalValueTax=value * 0.03;
			Stamp_duty=value *0.02;
			TotalTax=GetAdvanceIncomeTax() + CapitalValueTax + Stamp_duty;
			cout<<"\nPurchaser Tax"<<endl<<"-------------"<<endl<<endl;
			TaxPayerInfo();
			cout<<"Capital Value Tax: "<<CapitalValueTax<<endl;
			cout<<"Stamp Duty: "<<Stamp_duty<<endl;
			cout<<"Income Tax: "<<GetAdvanceIncomeTax()<<endl;
			cout<<"Total Tax of Purchaser: "<<TotalTax<<endl;
		}
};


int main()
{
	Seller seller((char*)"Kamran", 500000, 300000, (char*)"Filer", 2);
	Purchaser purchaser((char*)"Bilal", 500000, (char*)"Non-Filer");
	TaxPayer *obj[2];
	
	obj[0]=&seller;
	obj[1]=&purchaser;
	for(int i=0; i<2; i++)
	obj[i]->Calculate_Total_Tax();
	
	system("pause");
}
