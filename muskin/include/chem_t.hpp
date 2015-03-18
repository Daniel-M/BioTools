class chem_t
{
	private:

		std::string sChemName; /*!< String that names the chemical complex.*/
		
		double dInitialCondition;	/*!< Initial condition of the complex.*/
		
		double dValue; /*!< The chemical species value.*/

	public:
			
		/*!\brief Standard constructor. Sets all values to 0 and "".*/
		chem_t();
		
		/*!\brief Constructor. Sets the value of the chemical species to dValue_ the remaining are set to 0 and "".
		 *\param dValue_ The value to be stored on the chemical species.
		 */
		chem_t(double dValue_);

		/*!\brief Constructor. Sets the value and initial condition of the chemical species.
		 * \param dValue_ The value to be stored on the chemical species.
		 * \param dInitialCondition_ The initial condition to be stored on the chemical species.
		 */
		chem_t(double dValue_, double dInitialCondition_);

		/*!\brief Constructor. Sets all the values of the chemical species.
		 * \param dValue_ The value to be stored on the chemical species.
		 * \param dInitialCondition_ The initial condition to be stored on the chemical species.
		 * \param sChemName_ The name of the chemical species.
		 */
		chem_t(double dValue_, double dInitialCondition_, std::string sChemName_);

		/*!\brief The assignation operator. Sets the value of the chemical species.
		 * \param dValue_ The value to be stored on the chemical species value.
		 */
		chem_t& operator=(const double dValue_);
		
		/*!\brief Double cast. Returns the value of the chemical species.
		 */
		operator double();
		
		/*!\brief Returns the chemical species value.*/
		double getValue();
		
		/*!\brief Sets the chemical species value.
		 * \param dValue_ the value to be set on the chemical species value.
		 */
		double setValue(const double dValue_);

		//point_t toDouble(std::vector <chem_t> vcChems);
		
		//friend std::vector< chem_t > toChem_t(point_t ptVector);

		friend	std::ostream& operator<<(std::ostream& outStream, chem_t& cChem);
};

/*! We daclared here this typedef
 * typedef std::vector<chem_t> chem_vector_t;
 * and not in the typedef.hpp file in order to prevent malfunction during compilation.*/
typedef std::vector<chem_t> chem_vector_t;

point_t toDouble(std::vector <chem_t> vcChems);
chem_vector_t toChem_t(point_t ptVector);
