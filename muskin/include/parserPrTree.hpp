// /*!\brief This function overloads the libboost::ptree::operator<< to stream \c libboost::ptree
/*! 
 * This function overloads the libboost::ptree::operator<< to provide streaming for \a libboost::ptree
 *
 * \param[in] outStream stream data type.
 * \param[in] prTree boost::property_tree::ptree container.
 * \return A ostream consisting of the information contained on the property tree
 */
std::ostream& operator<<(std::ostream& outStream, boost::property_tree::ptree& prTree);

