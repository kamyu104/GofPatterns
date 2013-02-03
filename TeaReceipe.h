namespace classic
{
    class TeaReceipe : public Receipe
    {
    public:
      TeaReceipe(int minutes)
      : Receipe()
      , m_minutes(minutes)
      {}

      virtual void brew()
      {
	cout << m_minutes << "min steeping Tea through filter\n";
      }

      virtual void addCondiments()
      {
	cout << "Adding Lemon\n";
      }

    private:
      int m_minutes;

      NO_COPY(TeaReceipe);
    };
}
