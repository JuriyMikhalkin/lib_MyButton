
class MyButtonCl 
{  
  public:
    MyButtonCl(int p_pinNum);
  	bool StatusPressed();     // true, если кнопка в нажатом состоянии 
   	bool StatusReleased();    // true, если кнопка в отжатом состоянии
    bool StatusHolded();      // true, если кнопку зажимали pHoldedTime млсекунд и продолжают держать
  	bool EventPressed();      // true, если кнопка перешла в нажатое состояние (срабатывает один раз и больше не сработает пока кнопку не отпустят и снова не нажмут)
  	bool EventReleased();     // true, если кнопка перешла в отжатое состояние (срабатывает один раз и больше не сработает пока кнопку не нажмут и снова не отпустят)
  	bool EventHolded();       // true, если кнопка была зажата pHoldedTime млсекунд (срабатывает один раз)
  	bool EventClicked();      // true, если кнопку нажали и отпустили и при этом во время нажатия она не была удержанной
  
  private:
  	int pinNum;  
    int pHoldedTime=3000;
    unsigned long  last_update_time;   // время последнего считывания пина
    unsigned long  current_state_time; // время нахождения в текущем статусе 
    unsigned long  previous_state_msec; // милисекунд нахождения в предыдущем статусе   
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
    released_event_detected_early = true; // изначально кнопка отжата, поэтому чтобы она не сработала по умолчанию на старте тут true
    clicked_event_detected_early = true; 
};

void MyButtonCl::UpdateStatus() 
{
  bool vstate;
  if (millis()-last_update_time > 50) // нивелирует дребезг контактов, а также позволяет не задергивать кнопку, если подряд вызывается несколько функций о статусе или событии
  {
    vstate = !digitalRead(pinNum);
    last_update_time = millis();
    if (vstate != current_state)
    {
        current_state = vstate;
        previous_state_msec = millis()-current_state_time;      
    	current_state_time = millis(); // при смене статуса кнопки начинаем отсчет времени, сколько она живет в этом статусе
    	hold_event_detected_early = false;   // при смене статуса флаг, что удержание уже было обнаружено, скидываем
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

MyButtonCl c_ledBtn(2); // создание кнопки на втором пине

void setup()
{ 
  Serial.begin(9600);
}

void loop()
{

/*

bool EventClicked();      // true, если кнопку нажали и отпустили и при этом во время нажатия она не была удержанной
if (c_ledBtn.EventClicked())
  {
   Serial.println("EventClicked");
  }    
  
// true, если кнопка перешла в отжатое состояние (срабатывает один раз и больше не сработает пока кнопку не нажмут и снова не отпустят)
if (c_ledBtn.EventReleased())
  {
   Serial.println("EventReleased");
  }    
    
// true, если кнопка перешла в нажатое состояние (срабатывает один раз и больше не сработает пока кнопку не отпустят и снова не нажмут)
if (c_ledBtn.EventPressed())
  {
   Serial.println("EventPressed");
  }    

// true, если кнопка была зажата pHoldedTime млсекунд (срабатывает один раз)
if (c_ledBtn.EventHolded())
  {
   Serial.println("EventHolded");
  }    
    
// true, если кнопку зажимали pHoldedTime млсекунд и продолжают держать
if (c_ledBtn.StatusHolded())
  {
   Serial.println("StatusHolded");
  }    

// true, если кнопка в нажатом состоянии 
if (c_ledBtn.StatusPressed())
  {
   Serial.println("StatusPressed");
  }    

// true, если кнопка в отжатом состоянии
if (c_ledBtn.StatusReleased())
  {
   Serial.println("StatusReleased");
  }   
*/
}
 
  
