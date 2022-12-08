template<typename T>
class Smart_ptr
{
    private:
        T* m_ptr;

    public:
        Smart_ptr(T* ptr = nullptr)
            : m_ptr(ptr)
        {}

        ~Smart_ptr()
        {
            delete m_ptr;
        }

        Smart_ptr(Smart_ptr&& source) noexcept
            : m_ptr(source.m_ptr)
            {
                source.m_ptr = nullptr;
            }

        Smart_ptr& operator=(Smart_ptr&& source) noexcept
        {
            if (&source == this)
                return *this;

            delete m_ptr;

            m_ptr = source.m_ptr;
            source.m_ptr = nullptr;

            return *this;
        }

        Smart_ptr(const Smart_ptr& a) = delete;
        Smart_ptr& operator=(const Smart_ptr& a) = delete;

        T& operator*() const { return *m_ptr; }
        T* operator->() const { return m_ptr; }
        bool isNull() const { return m_ptr == nullptr; }
};
