namespace classic
{
    class Tea : public CaffeineBeverage
    {
    public:
      Tea()
	: CaffeineBeverage(m_receipe)
	, m_receipe(4)
      {}

    private:
      TeaReceipe m_receipe;
      NO_COPY(Tea);
    };
}
