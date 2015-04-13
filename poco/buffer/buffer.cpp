#include "Poco/Buffer.h"

#include <cstring>
#include <cstddef>

#include "buffer.h"

namespace MirrorLink {

    template<typename T>
        Buffer<T>::Buffer(std::size_t capacity)
        {
            buffer = new Poco::Buffer<T>(capacity);
        }

    template<typename T>
        Buffer<T>::Buffer(T* pMem, std::size_t length)
        {
            buffer = new Poco::Buffer<T>(pMem, length);
        }

    template<typename T>
        Buffer<T>::Buffer(const T* pMem, std::size_t length)
        {
            buffer = new Poco::Buffer<T>(pMem, length);
        }

    template<typename T>
        Buffer<T>::Buffer(const Buffer<T>& other)
        {
            buffer = new Poco::Buffer<T>(*other.buffer);
        }

    template<typename T>
        Buffer<T>& Buffer<T>::operator = (const Buffer<T>& other)
        {
            buffer = other.buffer;
            return *this;
        }

    template<typename T>
        Buffer<T>::~Buffer()
        {
            delete buffer;
        }

    template<typename T>
        void Buffer<T>::resize(std::size_t newCapacity, bool preserveContent)
        {
            buffer->resize(newCapacity, preserveContent);
        }

    template<typename T>
        void Buffer<T>::setCapacity(std::size_t newCapacity, bool preserveContent)
        {
            buffer->setCapacity(newCapacity, preserveContent);
        }

    template<typename T>
        void Buffer<T>::assign(const T* buf, std::size_t sz)
        {
            buffer->assign(buf, sz);
        }

    template<typename T>
        void Buffer<T>::append(const T* buf, std::size_t sz)
        {
            buffer->append(buf, sz);
        }

    template<typename T>
        void Buffer<T>::append(T val)
        {
            buffer->append(val);
        }

    template<typename T>
        void Buffer<T>::append(const Buffer<T>& buf)
        {
            buffer->append(*buf.buffer);
        }

    template<typename T>
        std::size_t Buffer<T>::capacity() const
        {
            return buffer->capacity();
        }

    template<typename T>
        std::size_t Buffer<T>::capacityBytes() const
        {
            return buffer->capacityBytes();
        }

    template<typename T>
        void Buffer<T>::swap(Buffer<T>& other)
        {

        }

    template<typename T>
        bool Buffer<T>::operator == (const Buffer<T>& other) const
        {
            return buffer == other.buffer;
        }

    template<typename T>
        bool Buffer<T>::operator != (const Buffer<T>& other) const
        {
            return buffer != other.buffer;
        }

    template<typename T>
        void Buffer<T>::clear()
        {
            buffer->clear();
        }

    template<typename T>
        std::size_t Buffer<T>::size() const
        {
            return buffer->size();
        }

    template<typename T>
        std::size_t Buffer<T>::sizeBytes() const
        {
            return buffer->sizeBytes();
        }

    template<typename T>
        T* Buffer<T>::begin()
        {
            return buffer->begin();
        }

    template<typename T>
        const T* Buffer<T>::begin() const
        {
            return const_cast<T*>(buffer->begin());
        }

    template<typename T>
        T* Buffer<T>::end()
        {
            return buffer->end();
        }

    template<typename T>
        const T* Buffer<T>::end() const
        {
            return const_cast<T*> (buffer->end());
        }

    template<typename T>
        bool Buffer<T>::empty() const
        {
            return buffer->empty();
        }

    template<typename T>
        T& Buffer<T>::operator [] (std::size_t index)
        {
            return buffer->operator[](index);
        }

    template<typename T>
        const T& Buffer<T>::operator [] (std::size_t index) const
        {
            return const_cast<T&> (buffer->operator[](index));
        }

    template class Buffer<char>;

} // namespace MirrorLink

