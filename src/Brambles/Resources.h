
#include<iostream>
#include<vector>

namespace Brambles
{
    struct Resource;

    /**
     * @brief Handles loading and caching of resources.
     */
    struct Resources
    {
        /**
         * @brief Loads a resource of type T from the given path, returning a shared pointer.
         * If already loaded, returns the cached resource.
         * @tparam T The type of resource.
         * @param _path The resource path.
         * @return A shared pointer to the loaded resource.
         */
        template <typename T>
        std::shared_ptr<T> load(const std::string& _path)
        {
            for (size_t i = 0; i < m_resources.size(); ++i)
            {
                if (m_resources.at(i)->getPath() == _path)
                {
                    return std::dynamic_pointer_cast<T>(m_resources.at(i));
                }
            }

            std::shared_ptr<T> rtn = std::make_shared<T>();
            rtn->m_path = _path;
            rtn->load();
            m_resources.push_back(rtn);
            return rtn;
        }

    private:
        std::vector<std::shared_ptr<Resource>> m_resources;
    };

}
