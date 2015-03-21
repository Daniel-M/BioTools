class system_t
{
	private:

		std::vector<chem_t> vcChems;  /*!< The set of chemical species contained on the system_t.*/

		std::vector<floating_t> vdKParameters;  /*!< .*/


	public:
		
		/*!\brief Standard constructor.*/
		system_t();
		
		/*!\brief Constructor. Uses the vector of chemicals and parameters \c chem_t.
		 * \param vcChems_ vector of \c chem_t objects representing chemical especies.
		 * \param vdKParameters_ Vector containing the set of parameters associated to the \c system_t object.*/
		system_t(std::vector<chem_t> vcChems_, std::vector<floating_t> vdKParameters_);

		///*!\brief Checks that the stored \c chem_t are well ordered within the \c system_t.*/
		/* Check that the indexes correspond to the chemical especies on veChem */
		//int_t checkCoherence();

		/**/
		//void operator()( const std::vector<floating_t> &y , std::vector<floating_t> &f , const floating_t /* t */ )
		void operator()( const std::vector<chem_t> &y , std::vector<floating_t> &f , const floating_t /* t */ );

		/*!\brief Overwrite the vector of \c chem_t objects of the \c system_t objects.
		 * \param vcChems_ The vector of \c chem_t objects to do the replacement.*/
		system_t& operator=(const std::vector<chem_t> vcChems_);
		
		/*!\brief Overwrite the vector of \c floating_t describing the parameters of the \c system_t object.
		 * \param vdKParameters_ the set of parameters of the system_t object.*/
		system_t& operator=(const std::vector<floating_t> vdKParameters_);

		/*!\brief Overwrite the vector of \c chem_t objects of the \c system_t objects.
		 * \param vcChems_ The vector of \c chem_t objects to do the replacement.*/
		void addchem_t(const std::vector<chem_t> cChem_);

		/*!\brief Overwrite the vector of \c floating_t describing the parameters of the \c system_t object.
		 * \param vdKParameters_ the set of parameters of the system_t object.*/
		void setParameters(const std::vector<floating_t> vdKParameters_);
};
