class Statistics {
public:
	Statistics(const Statistics&) = delete; // copy-constructor
	inline static Statistics& Get()
	{
		static Statistics m_Instance;
		return m_Instance;
	}
	inline unsigned int CurrentHeapUsage() { return AllocatedMemory - FreedMemory; }
public:
	unsigned int AllocatedMemory;
	unsigned int FreedMemory;
protected:
	Statistics() = default; // default constructor
};