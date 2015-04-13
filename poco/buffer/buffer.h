#include <cstddef>

namespace Poco
{
    namespace Net
    {
        class Socket;
    }

    template <typename T>
        class Buffer;
    
}


namespace MirrorLink {

template <typename T>
class Buffer
{
public:
	Buffer(std::size_t capacity);

	Buffer(T* pMem, std::size_t length);

	Buffer(const T* pMem, std::size_t length);

	Buffer(const Buffer& other);

	Buffer& operator = (const Buffer& other);

	~Buffer();
	
	void resize(std::size_t newCapacity, bool preserveContent = true);
	
	void setCapacity(std::size_t newCapacity, bool preserveContent = true);

	void assign(const T* buf, std::size_t sz);

	void append(const T* buf, std::size_t sz);

	void append(T val);

	void append(const Buffer& buf);

	std::size_t capacity() const;

	std::size_t capacityBytes() const;

	void swap(Buffer& other);

	bool operator == (const Buffer& other) const;

	bool operator != (const Buffer& other) const;
	void clear();

	std::size_t size() const;

	std::size_t sizeBytes() const;
	
	T* begin();
	
	const T* begin() const;

	T* end();
	
	const T* end() const;
	
	bool empty() const;

	T& operator [] (std::size_t index);

	const T& operator [] (std::size_t index) const;

private:
    Poco::Buffer<T>* buffer;
    Poco::Net::Socket *s;

};


} // namespace MirrorLink

