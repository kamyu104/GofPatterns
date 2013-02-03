namespace classic
{
    class Condiment
    {
    public:
      Condiment()
	: m_next(0)
      {}

      Condiment(Condiment* next)
      : m_next(next)
      {}

      string description()
      {
	if(m_next) return this->onDescription() + m_next->description();
	return this->onDescription();
      }
      float price()
      {
	if(m_next) return this->onPrice() + m_next->price();
	return this->onPrice();
      }

    private:
      virtual string onDescription() = 0;
      virtual float onPrice() = 0;

      Condiment* m_next;
    };
}
