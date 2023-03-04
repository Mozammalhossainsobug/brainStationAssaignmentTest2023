#include<bits/stdc++.h>
using namespace std;

class Product
{
private:
    string name;
    double price;
    string description;

public:
    Product()
    {
    }
    Product(string name, double price, string description)
    {
        this->name = name;
        this->price = price;
        this->description = description;
    }

    string getName()
    {
        return name;
    }

    double getPrice()
    {
        return price;
    }

    string getDescription()
    {
        return description;
    }

    void setName(string name)
    {
        this->name = name;
    }

    void setPrice(double price)
    {
        this->price = price;
    }

    void setDescription(string description)
    {
        this->description = description;
    }
    ~Product(){};

};


class OrderDetail: public Product
{
private:
    Product* product;
    int quantity;

public:
    OrderDetail()
    {
    }
    OrderDetail(Product* product, int quantity)
    {
        this->product = product;
        this->quantity = quantity;
    }

    Product* getProduct()
    {
        return product;
    }

    int getQuantity()
    {
        return quantity;
    }
    void setQuantity(int tmpQuantity)
    {
        quantity = tmpQuantity;
    }

    double getTotalCost()
    {
        return quantity * product->getPrice();
    }
    ~OrderDetail(){}

};

class ShoppingCart : public OrderDetail
{
private:
    vector<OrderDetail *> shoppingCart;
    OrderDetail *orderDetail;
    double totalcost;
public:
    void addProduct(Product *product, int quantity)
    {
        orderDetail = new OrderDetail(product,quantity);
        shoppingCart.push_back(orderDetail);
        totalcost += orderDetail->getPrice() * orderDetail->getQuantity();
        cout << "Added successful" << endl << endl;
    }

    void removeProduct(Product *product)
    {
        for(int i=0; i<shoppingCart.size(); i++)
        {
            if(shoppingCart[i]->getProduct() == product)
            {
                shoppingCart.erase(shoppingCart.begin()+i);
                cout << "Removed successful" << endl << endl;
                break;
            }
        }
    }

    void updateQuantity(Product *product, int quantity)
    {
        for(int i=0; i<shoppingCart.size(); i++)
        {
            if(shoppingCart[i]->getProduct() == product)
            {
                shoppingCart[i]->setQuantity(quantity);
                cout << "Updated Sucessful" << endl << endl;
                break;
            }
        }
    }

    vector<OrderDetail*> getProductsQuantitys()
    {
        return shoppingCart;
    }

    double getTotalCost()
    {
        totalcost = 0;
        for(auto &details : shoppingCart)
        {
            OrderDetail *orderDetail = details;
            totalcost += orderDetail->getTotalCost();
        }

        return totalcost;
    }
};




class Order :public ShoppingCart
{
private:
    vector<OrderDetail*> orders;
    double finalCost;

public:
    Order(vector<OrderDetail*> orderDetail, double cost)
    {
        orders = orderDetail;
        finalCost = cost;
    }
    vector<OrderDetail*> getOrderlist()
    {
        return orders;
    }

    double getCost()
    {
        return finalCost;
    }
    ~Order(){};
};


void product_list()
{
    cout << "<--------------- Product List ------------->" << endl;
    cout << "1. Apple $10.0 Fruit" << endl;
    cout << "2. Orange $15.0 Fruit" << endl;
    cout << "3. Guava $2.0 Fruit" << endl;
    cout << "4. lichu $1.0 Fruit" << endl;
    cout << "5. Jackfruit $4.0 Fruit" << endl;
    cout << "6. Exit" << endl << endl;
    cout << "Which food do you like to buy?" <<endl;
}

void menu_list()
{
    cout << "<----------Main Menu------------->"<<endl;
    cout << "1. Do you want to see products?" <<endl;
    cout << "2. Do you want to see your shopping cart?" << endl;
    cout << "3. Do you want to see your order?" << endl;
    cout << "4. Exit"<<endl;
}

int main()
{

    ShoppingCart cart;
    Product *p;
    while(1)
    {
        menu_list();
        int var;
        cin >> var;

        switch(var)
        {
        case 1:
        {
            product_list();
            int op,qn;
            cin >> op;
            cout << "How many items do you want to buy?" << endl;
            cin>> qn;
            if(op == 1)
            {
                p = new Product("Apple",10.0,"Fruit");
                cart.addProduct(p,qn);

            }
            else if(op == 2)
            {
                p = new Product("Orange",15.0,"Fruit");
                cart.addProduct(p,qn);

            }
            else if(op == 3)
            {
                p = new Product("Guava",2.0,"Fruit");
                cart.addProduct(p,qn);

            }
            else if(op == 4)
            {
                p = new Product("lichu",1.0,"Fruit");
                cart.addProduct(p,qn);

            }
            else if(op == 5)
            {
                p = new Product("Jackfruit",4.0,"Fruit");
                cart.addProduct(p,qn);

            }
            else
            {
                cout << "Invalid option, try again" << endl;

            }

            break;
        }

        case 2:
        {
            cout << "<---------------------------- Showing Shopping Cart ------------------------------>"<<endl;
            cout << "Item_no" << "\t" << "Product" << "\t" << "Price" << "\t" << "Description" << "\t" << "Quantity"<<endl;
            int cnt = 1;
            for(auto &display : cart.getProductsQuantitys())
            {
                cout <<cnt++ <<"\t";
                Product *product = display->getProduct();
                cout << product->getName() << "\t" << product->getPrice() << "\t" << product->getDescription()<<"\t          "<<display->getQuantity()<<endl;

            }
            cout <<"Total cost " <<  cart.getTotalCost() << endl <<endl;

            cout << "What do you want to do?" << endl;
            cout << "1.Update " <<endl;
            cout << "2.Delete " << endl;
            cout << "3.Exit" << endl;
            int dcs;
            cin >> dcs;
            if(dcs == 1)
            {
                int item, quantity;
                cout << "Which item do you want to update?" << endl;
                cin >> item;
                cout << "Changed Quantiy? " << endl;
                cin >> quantity;


                if(item > cnt || item < 1)
                {
                    cout << "Invalid item selected" << endl;
                    break;
                }

                cnt = 1;

                for(auto &display : cart.getProductsQuantitys())
                {
                    if(cnt == item)
                    {
                        cart.updateQuantity(display->getProduct(),quantity);
                        break;
                    }
                    cnt++;
                }
            }
            else if(dcs == 2)
            {
                int item;
                cout << "Which item do you want to remove?" << endl;
                cin >> item;

                if(item > cnt || item < 1)
                {
                    cout << "Invalid item selected" << endl;
                    break;
                }

                cnt = 1;

                for(auto &display : cart.getProductsQuantitys())
                {
                    if(cnt == item)
                    {
                        cart.removeProduct(display->getProduct());
                        break;
                    }
                    cnt++;
                }
            }
            else{
                break;
            }
          break;
        }

        case 3: {
            cout << "<---------------------------- Showing Ordered list ------------------------------>"<<endl;
            cout << "Item_no" << "\t" << "Product" << "\t" << "Price" << "\t" << "Description" << "\t" << "Quantity"<<endl;
            int cnt = 1;
            Order placedOrder(cart.getProductsQuantitys(),cart.getTotalCost());
            vector<OrderDetail* >final_order = placedOrder.getOrderlist();
            for(int i=0; i<final_order.size(); i++)
            {
               Product *p = final_order[i]->getProduct();
               cout <<cnt++<<"\t"<< p->getName() << "\t" << p->getPrice() << "\t" << p->getDescription()<<"\t"<<final_order[i]->getQuantity()<<endl;
            }
            cout<<"Total Cost "<<placedOrder.getCost() <<endl;
            break;
        }

        case 4: {
            return 0;
        }

        }

    }
    return 0;
}

