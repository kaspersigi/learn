/// @file osutils.h
#include "types.h"
#include <semaphore.h>

/// @brief General portable semaphore class implementation
class Semaphore final
{
public:
    /// @brief  Static method to create an instance of Semaphore
    static Semaphore* Create();

    /// @brief  Method to delete an instance of Semaphore
    void Destroy();

    /// @brief  Decrement/wait indefinitely on Semaphore (equivalent to sem P)
    void Wait();

    /// @brief  Wait with timeout on the Semaphore
    Result TimedWait(unsigned int timeoutMilliseconds);

    /// @brief  Increment/signal a Semaphore (equivalent to sem V)
    void Signal();

protected:
    /// @brief Constructor for Semaphore object.
    Semaphore() = default;

    /// @brief Destructor for Semaphore object.
    ~Semaphore() = default;

    // Disable copy constructor and assignment operator
    Semaphore(const Semaphore&) = delete;
    Semaphore(Semaphore&&) = delete;
    Semaphore& operator = (const Semaphore&) = delete;
    Semaphore& operator = (Semaphore&&) = delete;

private:
    /// @brief  Initialize a newly created Semaphore object
    Result Initialize();
    sem_t m_semaphore; ///< (Linux) Semaphore
    bool m_validSemaphore; ///< (Linux) Indicates if underlying semaphore is valid
};