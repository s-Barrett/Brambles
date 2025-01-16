
#pragma once
#include <string>
#include <iostream>
#include "rend/rend.h"

namespace Brambles
{

    struct Core;



	/**
	 * @brief Abstract class representing a resource that can be loaded and accessed.
	 */
    struct Resources;

    /**
     * @brief Base class for resources that can be loaded from a file or path.
     * Derived classes should implement the onLoad function to specify how the resource is loaded.
     */
    struct Resource
    {
        /**
         * @brief Pure virtual function for loading the resource.
         * Derived classes must implement this function to load the resource.
         */
        virtual void onLoad() = 0;

        /**
         * @brief Retrieves the file path of the resource.
         * @return The path of the resource as a string.
         */
        std::string getPath() const;

    private:
        friend struct Brambles::Resources;

        /**
         * @brief The file path where the resource is located.
         */
        std::string m_path;

        /**
         * @brief Internal function for loading the resource.
         */
        void load();
    };

}
