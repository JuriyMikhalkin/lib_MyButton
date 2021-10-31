
class MyButtonCl 
{  
  public:
    MyButtonCl(int p_pinNum);
  	bool StatusPressed();     // true, ���� ������ � ������� ��������� 
   	bool StatusReleased();    // true, ���� ������ � ������� ���������
    bool StatusHolded();      // true, ���� ������ �������� pHoldedTime �������� � ���������� �������
  	bool EventPressed();      // true, ���� ������ ������� � ������� ��������� (����������� ���� ��� � ������ �� ��������� ���� ������ �� �������� � ����� �� ������)
  	bool EventReleased();     // true, ���� ������ ������� � ������� ��������� (����������� ���� ��� � ������ �� ��������� ���� ������ �� ������ � ����� �� ��������)
  	bool EventHolded();       // true, ���� ������ ���� ������ pHoldedTime �������� (����������� ���� ���)
  	bool EventClicked();      // true, ���� ������ ������ � ��������� � ��� ���� �� ����� ������� ��� �� ���� ����������
  
  private:
  	int pinNum;  
    int pHoldedTime=3000;
    unsigned long  last_update_time;   // ����� ���������� ���������� ����
    unsigned long  current_state_time; // ����� ���������� � ������� ������� 
    unsigned long  previous_state_msec; // ���������� ���������� � ���������� �������   
    bool current_state;
    bool hold_event_detected_early;
    bool pressed_event_detected_early;
    bool released_event_detected_early;
    bool clicked_event_detected_early; 
	void UpdateStatus();
};

MyButtonCl::MyButtonCl(int p_pinNum) 
{ 
	pinNum = p_pinNum;
 	pinMode(pinNum, INPUT_PULLUP);
    last_update_time = millis();
    current_state_time = millis();
    previous_state_msec = 0;
 	current_state = false;
    hold_event_detected_early = false;
    pressed_event_detected_early = false;
    released_event_detected_early = true; // ���������� ������ ������, ������� ����� ��� �� ��������� �� ��������� �� ������ ��� true
    clicked_event_detected_early = true; 
};

void MyButtonCl::UpdateStatus() 
{
  bool vstate;
  if (millis()-last_update_time > 50) // ���������� ������� ���������, � ����� ��������� �� ����������� ������, ���� ������ ���������� ��������� ������� � ������� ��� �������
  {
    vstate = !digitalRead(pinNum);
    last_update_time = millis();
    if (vstate != current_state)
    {
        current_state = vstate;
        previous_state_msec = millis()-current_state_time;      
    	current_state_time = millis(); // ��� ����� ������� ������ �������� ������ �������, ������� ��� ����� � ���� �������
    	hold_event_detected_early = false;   // ��� ����� ������� ����, ��� ��������� ��� ���� ����������, ���������
    	pressed_event_detected_early = false;
        released_event_detected_early = false;
        clicked_event_detected_early = false;
    }
  }
};

bool MyButtonCl::StatusPressed() 
{ 
   UpdateStatus(); 
   return current_state;
};
bool MyButtonCl::StatusReleased() 
{ 
   UpdateStatus(); 
   return !current_state;
};
bool MyButtonCl::StatusHolded() 
{ 
    UpdateStatus();       
    return (current_state && millis()-current_state_time >= pHoldedTime);
};

bool MyButtonCl::EventPressed() 
{
   bool v_result = false;
   if (StatusPressed() && !pressed_event_detected_early)
   {
	   pressed_event_detected_early = true;
       v_result = true;
   } 
  return (v_result);
};

bool MyButtonCl::EventReleased() 
{
   bool v_result = false;
   if (StatusReleased() && !released_event_detected_early)
   {
	   released_event_detected_early = true;
       v_result = true;
   } 
  return (v_result);
};

bool MyButtonCl::EventHolded() 
{ 
    bool v_result = false;
    if (StatusHolded() && !hold_event_detected_early)
    {
  		hold_event_detected_early = true;
        v_result = true;
    } 
    return (v_result);
};

bool MyButtonCl::EventClicked() 
{ 
   bool v_result = false;

   if (StatusReleased() && !clicked_event_detected_early && previous_state_msec<pHoldedTime)
   {
	   clicked_event_detected_early = true;
       v_result = true;
   } 

};

/**************************/

MyButtonCl c_ledBtn(2); // �������� ������ �� ������ ����

void setup()
{ 
  Serial.begin(9600);
}

void loop()
{

/*

bool EventClicked();      // true, ���� ������ ������ � ��������� � ��� ���� �� ����� ������� ��� �� ���� ����������
if (c_ledBtn.EventClicked())
  {
   Serial.println("EventClicked");
  }    
  
// true, ���� ������ ������� � ������� ��������� (����������� ���� ��� � ������ �� ��������� ���� ������ �� ������ � ����� �� ��������)
if (c_ledBtn.EventReleased())
  {
   Serial.println("EventReleased");
  }    
    
// true, ���� ������ ������� � ������� ��������� (����������� ���� ��� � ������ �� ��������� ���� ������ �� �������� � ����� �� ������)
if (c_ledBtn.EventPressed())
  {
   Serial.println("EventPressed");
  }    

// true, ���� ������ ���� ������ pHoldedTime �������� (����������� ���� ���)
if (c_ledBtn.EventHolded())
  {
   Serial.println("EventHolded");
  }    
    
// true, ���� ������ �������� pHoldedTime �������� � ���������� �������
if (c_ledBtn.StatusHolded())
  {
   Serial.println("StatusHolded");
  }    

// true, ���� ������ � ������� ��������� 
if (c_ledBtn.StatusPressed())
  {
   Serial.println("StatusPressed");
  }    

// true, ���� ������ � ������� ���������
if (c_ledBtn.StatusReleased())
  {
   Serial.println("StatusReleased");
  }   
*/
}
 
  
