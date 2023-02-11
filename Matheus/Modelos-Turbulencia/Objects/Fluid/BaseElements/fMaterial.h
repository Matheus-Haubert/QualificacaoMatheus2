class fMaterial
{
public:
    int Id;
    double mu;  // VISCOSIDADE CINEMÁTICA
    double rho; // MASSA ESPECÍFICA
    double nu;  // VISCOSIDADE DINÂMICA

    fMaterial() {}
    fMaterial(const int &_Id, const double &_mu, const double &_rho)
    {
        Id = _Id;
        mu = _mu;
        rho = _rho;
        nu = mu / rho;
    }
    ~fMaterial() {}
};